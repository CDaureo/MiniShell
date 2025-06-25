/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:39:35 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/25 17:17:23 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void ft_add_to_array(char ***array, const char *str)
{
    int len = 0;
    char **new_array;

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

    new_array[len] = ft_strdup(str);
    new_array[len + 1] = NULL;

    if (*array)
        free(*array);

    *array = new_array;
}
