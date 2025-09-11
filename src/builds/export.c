/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:31:08 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 16:36:54 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env_list(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->key)
		{
			if (env_list->value)
				printf("declare -x %s=\"%s\"\n", env_list->key,
					env_list->value);
			else
				printf("declare -x %s\n", env_list->key);
		}
		env_list = env_list->next;
	}
}

static void	process_export_arg(char *arg, t_ms *ms)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_strndup(arg, eq - arg);
		value = ft_strdup(eq + 1);
		update_env_var(ms->env_list, key, value);
		free(key);
		free(value);
	}
	else
		update_env_var(ms->env_list, arg, NULL);
}

int	ft_export(char **argv, t_ms *ms)
{
	int	i;

	if (!argv[1])
	{
		print_env_list(ms->env_list);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		process_export_arg(argv[i], ms);
		i++;
	}
	return (0);
}
