/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:30 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/17 01:08:15 by cdaureo-         ###   ########.fr       */
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
	if (cmd->str && handle_builds(cmd->str, ms))
		restore_std_and_exit(stdout_copy, stdin_copy, 0);
	exec_child_cmd(cmd, ms, stdout_copy, stdin_copy);
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
