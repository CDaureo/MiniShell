/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:05:49 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 16:29:58 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>

int	ft_cd(char **argv, t_ms *ms)
{
	char	*dir;
	char	oldpwd[PATH_MAX];
	char	cwd[PATH_MAX];

	if (!argv[1])
	{
		dir = get_env_value(ms->env_list, "HOME");
		if (!dir)
			return (ft_putendl_fd("cd: HOME not set", 2), 1);
	}
	else
		dir = argv[1];
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		oldpwd[0] = '\0';
	if (chdir(dir) != 0)
	{
		fprintf(stderr, "cd: %s: ", dir);
		return (perror(""), 1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		update_env_var(ms->env_list, "OLDPWD", oldpwd);
		update_env_var(ms->env_list, "PWD", cwd);
	}
	return (0);
}
