/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 00:57:48 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/25 16:51:36 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_error(char *cmd, char *arg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
}

void	free_exit(t_simple_cmds *cmds, char *line)
{
	free_simple_cmds(cmds);
	free(line);
	printf("exit\n");
	exit(0);
}

void	closer(int stdout_copy, int stdin_copy)
{
	dup2(stdout_copy, STDOUT_FILENO);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdout_copy);
	close(stdin_copy);
}

void	execute_external_cmd(t_simple_cmds *cmds, t_ms *ms,
			int stdout_copy, int stdin_copy)
{
	pid_t	pid;
	int		status;

	(void)ms;
	(void)stdout_copy;
	(void)stdin_copy;
	pid = fork();
	if (pid == 0)
	{
		execvp(cmds->str[0], cmds->str);
		perror("execvp");
		exit(127);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
}

void	execute_cmds(t_simple_cmds *cmds, t_ms *ms, char *line)
{
	int	stdout_copy;
	int	stdin_copy;

	if (cmds && cmds->next)
		execute_pipeline(cmds, ms);
	else if (cmds)
	{
		if (cmds->str && cmds->str[0] && ft_strcmp(cmds->str[0], "exit") == 0)
			free_exit(cmds, line);
		if (!cmds->str || !cmds->str[0])
			return (closer(stdout_copy, stdin_copy), \
				apply_redirections(cmds, ms, &stdout_copy, &stdin_copy));
		if (is_builtin(cmds->str[0]))
		{
			apply_redirections(cmds, ms, &stdout_copy, &stdin_copy);
			ms->exit_status = handle_builds(cmds->str, ms);
			closer(stdout_copy, stdin_copy);
		}
		else
		{
			apply_redirections(cmds, ms, &stdout_copy, &stdin_copy);
			execute_external_cmd(cmds, ms, stdout_copy, stdin_copy);
			closer(stdout_copy, stdin_copy);
		}
	}
}
