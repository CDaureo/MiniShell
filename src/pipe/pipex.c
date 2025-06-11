/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:34:13 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/11 13:06:35 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Esta función convierte una lista de tokens en un array de strings
//para pasar directamente a execve.
char **tokens_to_str(t_token *tokens)
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

static void	run_command_in_pipeline(
    t_token *start_cmd, t_token *tmp_tokens, int previous_fd, char **envp, t_ms *ms)
{
    int fd[2];
    char **argv = tokens_to_str(start_cmd);
    char *path = get_cmd_path(argv[0], envp);

    if (tmp_tokens)
    {
        pipe(fd);
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
    if (previous_fd != -1)
    {
        dup2(previous_fd, STDIN_FILENO);
        close(previous_fd);
    }

    // Ejecutar builtins en el hijo si están en una tubería
    if (argv[0] && handle_builds(argv, ms))
        exit(0);

    if (path)
    {
        execve(path, argv, envp);
		free(path);
    }
    error_msg(argv[0]);
    exit(1);
}

void execute_pipeline(t_token *tokens, char **envp, t_ms *ms)
{
    pid_t pid;
    t_token *start_cmd = tokens;
    t_token *tmp_tokens = tokens;
    int previous_fd = -1;
    int fd[2];

    while (start_cmd)
    {
        tmp_tokens = start_cmd;
        while (tmp_tokens && tmp_tokens->type != TOKEN_PIPE)
            tmp_tokens = tmp_tokens->next;

        if (tmp_tokens)
            pipe(fd);

        pid = fork();
        if (pid < 0)
            error_msg("Error al crear el proceso hijo");
        if (pid == 0)
            run_command_in_pipeline(start_cmd, tmp_tokens, previous_fd, envp, ms);

        if (previous_fd != -1)
            close(previous_fd);
        if (tmp_tokens)
        {
            close(fd[1]);
            previous_fd = fd[0];
            start_cmd = tmp_tokens->next;
        }
        else
            start_cmd = NULL;
    }
    while (wait(NULL) != -1)
        ;
}
