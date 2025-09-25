/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:30 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/25 14:08:59 by cdaureo-         ###   ########.fr       */
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
static void	restore_std_and_exit(int stdout_copy, int stdin_copy, int exit_code)
{
	dup2(stdout_copy, STDOUT_FILENO);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdout_copy);
	close(stdin_copy);
	exit(exit_code);
}

static void	exec_child_cmd(t_simple_cmds *cmd, t_ms *ms,
			int stdout_copy, int stdin_copy)
{
	char	*path;

	if (!cmd->str || !cmd->str[0])
		restore_std_and_exit(stdout_copy, stdin_copy, 0);
	path = get_cmd_path(cmd->str[0], ms->envp);
	if (path)
	{
		execve(path, cmd->str, ms->envp);
		free(path);
	}
	error_msg(cmd->str[0]);
	restore_std_and_exit(stdout_copy, stdin_copy, 1);
}

static void	child_proc(t_simple_cmds *cmd, int prev_fd, int *fd, t_ms *ms)
{
	int	stdout_copy;
	int	stdin_copy;

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
	apply_redirections(cmd, ms, &stdout_copy, &stdin_copy);
	if (cmd->str && is_builtin(cmd->str[0]))
	{
		int exit_code = handle_builds(cmd->str, ms);
		restore_std_and_exit(stdout_copy, stdin_copy, exit_code);
	}
	exec_child_cmd(cmd, ms, stdout_copy, stdin_copy);
}

static pid_t	fork_and_run(t_simple_cmds *cmd, int prev_fd, int *fd, t_ms *ms)
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
	return (pid);
}

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

	while ((pid = wait(&status)) != -1)
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
