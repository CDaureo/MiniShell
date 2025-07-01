/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:55:25 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/07/01 17:55:33 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_unset(char **argv, t_ms *ms)
{
    int i = 1;
    if (!argv[1])
        return (0);
    while (argv[i])
    {
        t_env *prev = NULL;
        t_env *curr = ms->env_list;
        while (curr)
        {
            if (ft_strcmp(curr->key, argv[i]) == 0)
            {
                if (prev)
                    prev->next = curr->next;
                else
                    ms->env_list = curr->next;
                free(curr->key);
                free(curr->value);
                free(curr);
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        i++;
    }
    return (0);
}

