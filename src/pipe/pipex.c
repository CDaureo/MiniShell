/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:30 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/25 15:18:41 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*static void	set_redirs(int prev_fd, int *fd)
{
	if (fd)
	{
		dup2(fd[1], STDOUT_FILENO);
		if (!fd)
			return ;
		close(fd[0]);
		close(fd[1]);
	}
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}
*/

static void	setup_pipe_or_end(t_simple_cmds *cmds, int fd[2])
{
	if (cmds->next && pipe(fd) < 0)
		error_msg("pipe");
	else if (!cmds->next)
	{
		fd[0] = -1;
		fd[1] = -1;
	}
}

static void	handle_pipe_cleanup(int *prev_fd, int fd[2], t_simple_cmds *cmds)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmds->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

static pid_t	execute_all_commands(t_simple_cmds *cmds, t_ms *ms)
{
	int		prev_fd;
	int		fd[2];
	pid_t	last_pid;
	pid_t	pid;

	prev_fd = -1;
	last_pid = -1;
	while (cmds)
	{
		setup_pipe_or_end(cmds, fd);
		pid = fork_and_run(cmds, prev_fd, fd, ms);
		if (!cmds->next)
			last_pid = pid;
		handle_pipe_cleanup(&prev_fd, fd, cmds);
		cmds = cmds->next;
	}
	return (last_pid);
}

static void	wait_for_last_process(pid_t last_pid, t_ms *ms)
{
	pid_t	pid;
	int		status;

	pid = wait(&status);
	while (pid != -1)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				ms->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				ms->exit_status = 128 + WTERMSIG(status);
		}
	}
}

void	execute_pipeline(t_simple_cmds *cmds, t_ms *ms)
{
	pid_t	last_pid;

	last_pid = execute_all_commands(cmds, ms);
	wait_for_last_process(last_pid, ms);
}
