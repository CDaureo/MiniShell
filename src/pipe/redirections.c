/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:05:18 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 18:13:45 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_outfile_trunc(char *filename, t_ms *ms)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		ms->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		ms->exit_status = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	open_outfile_append(char *filename, t_ms *ms)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		ms->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		ms->exit_status = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	open_infile(char *filename, t_ms *ms)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		ms->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		ms->exit_status = 1;
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_token(t_token *redir, t_ms *ms)
{
	if (redir->type == TOKEN_REDIRECT)
		return (open_outfile_trunc(redir->value, ms));
	else if (redir->type == TOKEN_APPEND)
		return (open_outfile_append(redir->value, ms));
	else if (redir->type == TOKEN_INPUT || redir->type == TOKEN_HEREDOC)
		return (open_infile(redir->value, ms));
	return (0);
}

void	apply_redirections(t_simple_cmds *cmd, t_ms *ms)
{
	int		ret;
	t_token	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		ret = handle_redir_token(redir, ms);
		if (ret < 0)
			return ;
		redir = redir->next;
	}
}
