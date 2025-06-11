/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:39:35 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/11 14:02:40 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	empty_array(char ***array, const char *new_str)
{
	char	**new_array;
	
    if (*array == NULL)
    {
        new_array = malloc(2 * sizeof(char *));
        if (!new_array)
            return (-1);
        new_array[0] = ft_strdup(new_str);
        if (!new_array[0])
        {
            free(new_array);
            return (-1);
        }
        new_array[1] = NULL;
        *array = new_array;
        return (0);
    }
	return (1);
}

int ft_add_to_array(char ***array, const char *new_str)
{
    char	**new_array;
    size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
    if(empty_array(array, new_str) == 0)
		return(0);
	while ((*array)[i])
        i++;
    new_array = malloc((i + 2) * sizeof(char *));
    if (!new_array)
		return (-1);
	while(j < i)
	{
		new_array[j] = (*array)[j];
		j++;
	}
    new_array[i] = ft_strdup(new_str);
    if (!new_array[i])
        return (free(new_array), -1);
    new_array[i + 1] = NULL;
    free(*array);
    *array = new_array;
    return (0);
}
