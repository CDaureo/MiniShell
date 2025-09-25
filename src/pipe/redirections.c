/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 01:00:10 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/25 17:18:33 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

static void	read_heredoc_input(int write_fd, char *delimiter)
{
	char	*line;
	size_t	delim_len;

	delim_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) == delim_len && ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

static int	handle_heredoc(char *delimiter, t_ms *ms)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		ms->exit_status = 1;
		return (-1);
	}
	read_heredoc_input(pipefd[1], delimiter);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		ms->exit_status = 1;
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}

static int	handle_redir_token(t_token *redir, t_ms *ms)
{
	if (redir->type == TOKEN_REDIRECT)
		return (open_outfile_trunc(redir->value, ms));
	else if (redir->type == TOKEN_APPEND)
		return (open_outfile_append(redir->value, ms));
	else if (redir->type == TOKEN_INPUT)
		return (open_infile(redir->value, ms));
	else if (redir->type == TOKEN_HEREDOC)
		return (handle_heredoc(redir->value, ms));
	return (0);
}

void	apply_redirections(t_simple_cmds *cmd, t_ms *ms,
			int *stdout_copy, int *stdin_copy)
{
	int		ret;
	t_token	*redir;

	*stdout_copy = dup(STDOUT_FILENO);
	*stdin_copy = dup(STDIN_FILENO);
	redir = cmd->redirections;
	while (redir)
	{
		ret = handle_redir_token(redir, ms);
		if (ret < 0)
			return ;
		redir = redir->next;
	}
}
