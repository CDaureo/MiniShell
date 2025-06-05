/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:08:09 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/05 17:29:07 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_envp(char **envp)
{
	int i;
	i = 0;
	while (envp[i])
		i++;
	return (i);
}
char **copy_envp(char **envp)
{
    int count = count_envp(envp);
    char **copy = malloc(sizeof(char *) * (count + 1));
    int i = 0;
    if (!copy)
        return NULL;
    while (envp[i])
    {
        copy[i] = ft_strdup(envp[i]);
        i++;
    }
    copy[i] = NULL;
    return copy;
}

/*void update_envp(t_env **envp, const char *key, const char *value)
{
	while (envp);
}
	*/
