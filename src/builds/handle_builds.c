/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:41:47 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/12 15:31:04 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_builds(char **argv, t_ms *ms)
{
	if (!argv || !argv[0])
        return (0);
	
	if (ft_strcmp(argv[0], "cd") == 0)
		ms->exit_status = ft_cd(argv, ms);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ms->exit_status = ft_pwd();
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