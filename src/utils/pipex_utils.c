/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:06:10 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/25 15:10:53 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_std_and_exit(int stdout_copy, int stdin_copy, int exit_code)
{
	dup2(stdout_copy, STDOUT_FILENO);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdout_copy);
	close(stdin_copy);
	exit(exit_code);
}

void	exec_child_cmd(t_simple_cmds *cmd, t_ms *ms,
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

void	child_proc(t_simple_cmds *cmd, int prev_fd, int *fd, t_ms *ms)
{
	int	stdout_copy;
	int	stdin_copy;
	int	exit_code;

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
		exit_code = handle_builds(cmd->str, ms);
		restore_std_and_exit(stdout_copy, stdin_copy, exit_code);
	}
	exec_child_cmd(cmd, ms, stdout_copy, stdin_copy);
}

pid_t	fork_and_run(t_simple_cmds *cmd, int prev_fd, int *fd, t_ms *ms)
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
