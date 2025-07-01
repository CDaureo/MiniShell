/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:39:35 by simgarci          #+#    #+#             */
/*   Updated: 2025/07/01 14:18:53 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"

void ft_add_to_array(char ***array, const char *str, int last_exit_status)
{
    int len;
    char **new_array;
    const char *to_add;
	char *expanded;
	const char *env_var_name;
	char exit_status_str[12];

	len = 0;
	to_add = str;
    if (ft_strcmp(str, "$?") == 0)
    {
		printf("Adding exit status: %d\n", last_exit_status);
        snprintf(exit_status_str, sizeof(exit_status_str), "%d", last_exit_status);
        to_add = exit_status_str;
    }
    else if(str[0] == '$')
    {
        env_var_name = str + 1;
        expanded = getenv(env_var_name);
        if (expanded)
            to_add = expanded;
        else
            to_add = "";
    }
    if (*array)
    {
        while ((*array)[len])
            len++;
    }

    new_array = malloc(sizeof(char *) * (len + 2));
    if (!new_array)
        return;

    for (int i = 0; i < len; i++)
        new_array[i] = (*array)[i];

    new_array[len] = ft_strdup(to_add);
    new_array[len + 1] = NULL;

    if (*array)
        free(*array);

    *array = new_array;
}
