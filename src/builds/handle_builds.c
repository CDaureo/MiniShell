/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:37:40 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/25 12:43:15 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_exit_status(char **argv, int exit_status)
{
	char	*status_str;
	int		i;

	i = 0;
	status_str = ft_itoa(exit_status);
	if (!status_str)
		return ;
	while (argv && argv[i])
	{
		if (ft_strcmp(argv[i], "$?") == 0)
		{
			free(argv[i]);
			argv[i] = ft_strdup(status_str);
		}
		i++;
	}
	free(status_str);
}

static int	exec_builtin(char **argv, t_ms *ms)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, ms));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(ms));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(ms));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, ms));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(argv, ms));
	else if (ft_strcmp(argv[0], "exit") == 0)
	{
		exit(0);
	}
	return (-1);
}

static int	exec_external(char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execvp(argv[0], argv);
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
	else
	{
		perror("fork");
		return (1);
	}
}

int	handle_builds(char **argv, t_ms *ms)
{
	int	ret;

	if (!argv || !argv[0])
		return (0);
	expand_exit_status(argv, ms->exit_status);
	ret = exec_builtin(argv, ms);
	if (ret != -1)
	{
		ms->exit_status = ret;
		return (ret);
	}
	else
	{
		ms->exit_status = exec_external(argv);
		return (ms->exit_status);
	}
}
