/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:34:13 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/04 13:16:29 by cdaureo-         ###   ########.fr       */
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
		return NULL;
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
	while(start_cmd)
	{
		tmp_tokens = start_cmd;
		while(tmp_tokens && tmp_tokens->type != TOKEN_PIPE)
			tmp_tokens = tmp_tokens->next;
		if (tmp_tokens)
			pipe(fd);

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // Proceso hijo
		{
			/* code */
		}
		
		
	}
}


