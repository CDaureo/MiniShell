/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:52:32 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 18:57:25 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_external_cmd(t_simple_cmds *cmds, t_ms *ms)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		apply_redirections(cmds, ms);
		execvp(cmds->str[0], cmds->str);
		perror("execvp");
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
}

void	execute_cmds(t_simple_cmds *cmds, t_ms *ms, char *line)
{
	if (cmds && cmds->next)
	{
		execute_pipeline(cmds, ms);
	}
	else if (cmds)
	{
		if (cmds->str && cmds->str[0] && ft_strcmp(cmds->str[0], "exit") == 0)
		{
			free_simple_cmds(cmds);
			free(line);
			printf("exit\n");
			exit(0);
		}
		if (is_builtin(cmds->str[0]))
		{
			apply_redirections(cmds, ms);
			ms->exit_status = handle_builds(cmds->str, ms);
		}
		else
		{
			execute_external_cmd(cmds, ms);
		}
	}
}
