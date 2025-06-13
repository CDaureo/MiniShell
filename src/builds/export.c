/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:05:53 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/13 18:09:07 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_export(char **argv, t_ms *ms)
{
	int i;

	i = 1;
	if (!argv)
	{
   		t_env *env_list = ms->env_list;
        while (env_list)
        {
            if (env_list->key)
            {
                if (env_list->value)
                    printf("declare -x %s=\"%s\"\n", env_list->key, env_list->value);
                else
                    printf("declare -x %s\n", env_list->key);
            }
            env_list = env_list->next;
        }
		return (0);
	}
	 while (argv[i])
    {
        char *eq = ft_strchr(argv[i], '=');
        if (eq) // Si el argumento tiene un "=" (ejemplo: VAR=value)
        {
            char *key = ft_strndup(argv[i], eq - argv[i]);
            char *value = ft_strdup(eq + 1);
            update_env_var(ms->env_list, key, value); // Actualizar o añadir la variable
            free(key);
            free(value);
        }
        else // Si el argumento no tiene "=" (ejemplo: VAR)
        {
            update_env_var(ms->env_list, argv[i], NULL); // Añadir la variable sin valor
        }
        i++;
    }
	return (0);
}