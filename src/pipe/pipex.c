/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:30 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/25 17:20:53 by simgarci         ###   ########.fr       */
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
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		child_proc(cmd, prev_fd, fd_ptr, ms);
	return (pid);
}

static int	setup_pipe(t_simple_cmds *cmds, int *fd)
{
	if (cmds->next && pipe(fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	else if (!cmds->next)
	{
		fd[0] = -1;
		fd[1] = -1;
	}
	return (0);
}

static void	execute_pipeline_loop(t_simple_cmds *cmds, t_ms *ms)
{
	int		prev_fd;
	int		fd[2];
	int		status;

	prev_fd = -1;
	while (cmds)
	{
		if (setup_pipe(cmds, fd) == -1)
			return ;
		if (fork_and_run(cmds, prev_fd, fd, ms) == -1)
			return ;
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmds = cmds->next;
	}
	while (wait(&status) != -1)
		;
}

void	execute_pipeline(t_simple_cmds *cmds, t_ms *ms)
{
	preprocess_heredocs(cmds);
	execute_pipeline_loop(cmds, ms);
}
