/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:41:47 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/11 13:07:28 by cdaureo-         ###   ########.fr       */
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
	{
	  	char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)))
            printf("%s\n", cwd);
        ms->exit_status = 0;
	}
	else if (ft_strcmp(argv[0], "exit") == 0)
    {
        ms->exit_status = 0;
        exit(0);
    }
	else
        return (0); // No es un builtin
	
	
	return(1);
}