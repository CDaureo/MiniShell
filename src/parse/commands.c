/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:09:18 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/25 15:24:01 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token_and_next(t_token *tok, int free_next)
{
	if (!tok)
		return ;
	if (tok->value)
		free(tok->value);
	if (free_next && tok->next)
	{
		if (tok->next->value)
			free(tok->next->value);
		free(tok->next);
	}
	free(tok);
}

char	*process_heredoc(const char *delimiter)
{
	int		fd;
	char	*line;
	char	*temp_file;
	static int	heredoc_count = 0;
	char	temp_name[50];

	sprintf(temp_name, "/tmp/heredoc_%d_%d", getpid(), heredoc_count++);
	temp_file = ft_strdup(temp_name);
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc temp file");
		free(temp_file);
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (temp_file);
}

void	command_tokens(t_simple_cmds **current_cmd, t_token **current_token)
{
	t_token	*redir;
	t_token	*tmp;
	char	*heredoc_file;

	if ((*current_token)->next)
	{
		redir = malloc(sizeof(t_token));
		if (redir)
		{
			if ((*current_token)->type == TOKEN_HEREDOC)
			{
				heredoc_file = process_heredoc((*current_token)->next->value);
				if (heredoc_file)
				{
					redir->type = TOKEN_INPUT;
					redir->value = heredoc_file;
					(*current_cmd)->hd_file_name = ft_strdup(heredoc_file);
				}
				else
				{
					free(redir);
					return ;
				}
			}
			else
			{
				redir->type = (*current_token)->type;
				redir->value = ft_strdup((*current_token)->next->value);
			}
			redir->next = (*current_cmd)->redirections;
			(*current_cmd)->redirections = redir;
			(*current_cmd)->num_redirections++;
		}
		tmp = *current_token;
		*current_token = (*current_token)->next->next;
		free_token_and_next(tmp, 1);
	}
	else
	{
		tmp = *current_token;
		*current_token = (*current_token)->next;
		free_token_and_next(tmp, 0);
	}
}
