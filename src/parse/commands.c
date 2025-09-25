/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:09:18 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/25 17:27:09 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*create_temp_file(void)
{
	static int	count;
	char		*temp_file;
	char		*count_str;
	char		*pid_str;

	pid_str = ft_itoa(getpid());
	count_str = ft_itoa(count++);
	temp_file = ft_strjoin("/tmp/heredoc_", pid_str);
	free(pid_str);
	pid_str = ft_strjoin(temp_file, "_");
	free(temp_file);
	temp_file = ft_strjoin(pid_str, count_str);
	free(pid_str);
	free(count_str);
	return (temp_file);
}

char	*process_heredoc(const char *delimiter)
{
	int		fd;
	char	*line;
	char	*temp_file;

	temp_file = create_temp_file();
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("heredoc temp file"), free(temp_file), NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			return (free(line), close(fd), temp_file);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	preprocess_heredocs(t_simple_cmds *cmds)
{
	t_simple_cmds	*cmd;
	t_token			*redir;
	char			*heredoc_file;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				heredoc_file = process_heredoc(redir->value);
				if (heredoc_file)
				{
					free(redir->value);
					redir->type = TOKEN_INPUT;
					redir->value = heredoc_file;
					cmd->hd_file_name = ft_strdup(heredoc_file);
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

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

void	command_tokens(t_simple_cmds **current_cmd, t_token **current_token)
{
	t_token	*redir;
	t_token	*tmp;

	if ((*current_token)->next)
	{
		redir = malloc(sizeof(t_token));
		if (redir)
		{
			redir->type = (*current_token)->type;
			redir->value = ft_strdup((*current_token)->next->value);
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
