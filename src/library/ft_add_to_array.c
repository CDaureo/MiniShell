/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:04:01 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 17:05:17 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"

static int	get_array_len(char **array)
{
	int	len;

	len = 0;
	if (array)
	{
		while (array[len])
			len++;
	}
	return (len);
}

static const char	*expand_str(const char *str, int last_exit_status)
{
	static char	exit_status_str[12];
	const char	*env_var_name;
	char		*expanded;

	if (ft_strcmp(str, "$?") == 0)
	{
		snprintf(exit_status_str, sizeof(exit_status_str),
			"%d", last_exit_status);
		return (exit_status_str);
	}
	else if (str[0] == '$')
	{
		env_var_name = str + 1;
		expanded = getenv(env_var_name);
		if (expanded)
			return (expanded);
		else
			return ("");
	}
	return (str);
}

void	ft_add_to_arr(char ***array, const char *str, int last_exit_status)
{
	const char	*to_add;
	int			len;
	char		**new_array;
	int			i;

	len = get_array_len(*array);
	to_add = expand_str(str, last_exit_status);
	new_array = malloc(sizeof(char *) * (len + 2));
	if (!new_array)
		return ;
	i = 0;
	while (i < len)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[len] = ft_strdup(to_add);
	new_array[len + 1] = NULL;
	if (*array)
		free(*array);
	*array = new_array;
}
