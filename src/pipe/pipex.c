/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:30 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/07/04 17:20:44 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_pipe(int *fd)
{
	if (!fd)
		return ;
	close(fd[0]);
	close(fd[1]);
}

static void	set_redirs(int prev_fd, int *fd)
{
	if (fd)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
	}
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

static void	child_proc(t_simple_cmds *cmd, int prev_fd, int *fd, t_ms *ms)
{
	char	*path;

	set_redirs(prev_fd, fd);
	apply_redirections(cmd, ms);
	if (cmd->str && handle_builds(cmd->str, ms))
		(exit(0));
	if (!cmd->str || !cmd->str[0])
		(exit(0));
	path = get_cmd_path(cmd->str[0], ms->envp);
	if (path)
	{
		execve(path, cmd->str, ms->envp);
		free(path);
	}
	error_msg(cmd->str[0]);
	(exit(1));
}

static void	fork_and_run(t_simple_cmds *cmd, int prev_fd, int *fd, t_ms *ms)
{
	pid_t	pid;
	int		*fd_ptr;

	if (cmd->next)
		fd_ptr = fd;
	else
		fd_ptr = NULL;
	pid = fork();
	if (pid < 0)
		error_msg("fork");
	if (pid == 0)
		child_proc(cmd, prev_fd, fd_ptr, ms);
}

void	execute_pipeline(t_simple_cmds *cmds, t_ms *ms)
{
	int	prev_fd;
	int	fd[2];

	prev_fd = -1;
	while (cmds)
	{
		if (cmds->next && pipe(fd) < 0)
			error_msg("pipe");
		else if (!cmds->next)
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		fork_and_run(cmds, prev_fd, fd, ms);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmds = cmds->next;
	}
	while (wait(NULL) != -1)
		;
}
