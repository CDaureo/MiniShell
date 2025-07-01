/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:41:47 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/07/01 17:57:50 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void expand_exit_status(char **argv, int exit_status)
{
    char status_str[12];
    snprintf(status_str, sizeof(status_str), "%d", exit_status);
    int i = 0;
    while (argv && argv[i])
    {
        if (strcmp(argv[i], "$?") == 0)
        {
            free(argv[i]);
            argv[i] = strdup(status_str);
        }
        i++;
    }
}

int	handle_builds(char **argv, t_ms *ms)
{
	if (!argv || !argv[0])
        return (0);
	
    expand_exit_status(argv, ms->exit_status);
		
	if (ft_strcmp(argv[0], "cd") == 0)
		ms->exit_status = ft_cd(argv, ms);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ms->exit_status = ft_pwd(ms);
	else if (ft_strcmp(argv[0], "echo") == 0)
		ms->exit_status = ft_echo(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		ms->exit_status = ft_env(ms);
	else if (ft_strcmp(argv[0], "export") == 0)
		ms->exit_status = ft_export(argv, ms);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ms->exit_status = ft_unset(argv, ms);

	
	else if (ft_strcmp(argv[0], "exit") == 0)
    {
        ms->exit_status = 0;
        exit(0);
    }
	else
	{
	pid_t pid = fork();
        if (pid == 0)
        {
            execvp(argv[0], argv);
            // Si execvp falla:
            fprintf(stderr, "%s: command not found\n", argv[0]);
            exit(127);
        }
        else if (pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
			if (WIFEXITED(status))
                ms->exit_status = WEXITSTATUS(status);
            else
                ms->exit_status = 1;      
		}
        else
        {
            perror("fork");
            ms->exit_status = 1;
        }
        return (1);	
	}
	return(1);
}