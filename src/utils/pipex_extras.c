/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:12:31 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/25 17:13:30 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"

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
	perror(cmd->str[0]);
	restore_std_and_exit(stdout_copy, stdin_copy, 127);
}

void	child_proc(t_simple_cmds *cmd, int prev_fd, int *fd, t_ms *ms)
{
	int	stdout_copy;
	int	stdin_copy;
	int	exit_code;

	if (fd)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	apply_redirections(cmd, ms, &stdout_copy, &stdin_copy);
	if (!cmd->str || !cmd->str[0])
		restore_std_and_exit(stdout_copy, stdin_copy, 0);
	if (cmd->str && is_builtin(cmd->str[0]))
	{
		exit_code = handle_builds(cmd->str, ms);
		restore_std_and_exit(stdout_copy, stdin_copy, exit_code);
	}
	exec_child_cmd(cmd, ms, stdout_copy, stdin_copy);
}
