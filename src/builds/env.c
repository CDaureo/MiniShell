/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:50:14 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 16:27:03 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_ms *ms)
{
	t_env	*env_list;

	env_list = ms->env_list;
	if (!ms || !ms->env_list)
		return (fprintf(stderr, "No environment variables set.\n"), 1);
	while (env_list)
	{
		if (env_list->key)
		{
			if (env_list->value)
				printf("%s=%s\n", env_list->key, env_list->value);
			else
				printf("%s=\n", env_list->key);
		}
		env_list = env_list->next;
	}
	return (0);
}
