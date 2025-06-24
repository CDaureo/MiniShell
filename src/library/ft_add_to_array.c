/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:39:35 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/24 12:16:47 by simgarci         ###   ########.fr       */
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

    // Check if the array is empty or if the new string is invalid
    if (empty_array(array, new_str) == 0)
    {
        printf("String '%s' was not added (empty_array check failed)\n", new_str);
        return (0);
    }

    // Count the current size of the array
    while ((*array)[i])
        i++;

    // Allocate memory for the new array
    new_array = malloc((i + 2) * sizeof(char *));
    if (!new_array)
    {
        printf("Failed to allocate memory for adding string '%s'\n", new_str);
        return (-1);
    }

    // Copy existing strings to the new array
    while (j < i)
    {
        new_array[j] = (*array)[j];
        j++;
    }

    // Duplicate the new string and add it to the array
    new_array[i] = ft_strdup(new_str);
    if (!new_array[i])
    {
        printf("Failed to duplicate string '%s'\n", new_str);
        free(new_array);
        return (-1);
    }

    // Null-terminate the new array
    new_array[i + 1] = NULL;

    // Free the old array and update the pointer
    free(*array);
    *array = new_array;

    // Print success message
    printf("Added string '%s' successfully\n", new_str);

    return (0);
}
