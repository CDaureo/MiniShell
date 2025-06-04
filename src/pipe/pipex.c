/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:34:13 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/04 13:42:12 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Esta función convierte una lista de tokens en un array de strings
//para pasar directamente a execve.
static char **tokens_to_str(t_token *tokens)
{
	int count;
	int i;
	t_token *tkn = tokens;
	char **argv;
	count = 0;
	i = 0;
	// Contar cuántos tokens son de tipo TOKEN_WORD seguidos (hasta PIPE o NULL)
	while(tkn && tkn->type != TOKEN_PIPE)
	{
		if (tkn->type == TOKEN_WORD || tkn->type == TOKEN_REDIRECT || 
				tkn->type == TOKEN_APPEND)
			count++;
		tkn = tkn->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	tkn = tokens;
	while (i < count)
	{
		argv[i] = ft_strdup(tkn->value);
		tkn = tkn->next;
		i++;
	}
	argv[i] = NULL;
	return argv;	
}

void execute_pipeline(t_token *tokens, char **envp)
{
	int fd[2];
	pid_t pid;
	t_token *start_cmd = tokens;
	t_token *tmp_tokens = tokens;
	int previous_fd = -1; //para almacenar el fd anterior

	while(start_cmd)
	{
		tmp_tokens = start_cmd;
		while(tmp_tokens && tmp_tokens->type != TOKEN_PIPE)
			tmp_tokens = tmp_tokens->next;
		if (tmp_tokens)
			pipe(fd);

		pid = fork();
		if (pid < 0)
			error_msg("Error al crear el proceso hijo");
		if (pid == 0) // Proceso hijo
		{
			if (previous_fd != -1)
			{
				close(fd[0]); // Cerrar el extremo de lectura del pipe anterior
				dup2(previous_fd, STDIN_FILENO); // Redirigir entrada estándar
				close(fd[1]); // Cerrar el fd anterior
			}
			char **argv = tokens_to_str(start_cmd);
			char *path = get_cmd_path(argv[0], envp);
			if (path)
			{
				execve(path, argv, envp);
				free(path);
			}
			if (!path || execve(path, argv, envp) == -1)
				error_msg("Error al ejecutar el comando");
		}
		if (previous_fd != -1)
			close(previous_fd); // Cerrar el fd anterior en el padre
		if (tmp_tokens)
		{
			close(fd[1]); // Cerrar el extremo de escritura del pipe actual
			previous_fd = fd[0]; // Guardar el fd de lectura para el siguiente comando
			start_cmd = tmp_tokens->next; // Avanzar al siguiente comando
		}
		else
			start_cmd = NULL; // No hay más comandos, salir del bucle
		while(wait(NULL) > 0); // Esperar a que el hijo termine
	}
}
