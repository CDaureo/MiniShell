/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:57:55 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/25 13:32:00 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/minishell.h"

static int	check_interrogation(char *dst, int *i, int last_exit_status)
{
	int		k;
	int		j;
	char	*es;

	k = 0;
	j = 0;
	es = ft_itoa(last_exit_status);
	if (!es)
		return (0);
	while (es[j])
		dst[k++] = es[j++];
	free(es);
	*i += 2;
	return (k);
}

static void	quote_handling(const char *str, char *res, int last_exit_status)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			j += handle_single_quote(res + j, str, &i);
		else if (str[i] == '"')
			j += handle_double_quote(res + j, str, &i, last_exit_status);
		else if (str[i] == '$' && str[i + 1] == '"')
		{
			i++;
			j += handle_double_quote(res + j, str, &i, last_exit_status);
		}
		else if (str[i] == '$')
			j += copy_var_value(res + j, str, &i, last_exit_status);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
}

int	copy_var_value(char *dst, const char *src, int *i, int last_exit_status)
{
	char	*val;
	char	var[256];
	int		k;
	int		j;

	k = 0;
	j = 0;
	if (!src[*i + 1])
		return (dst[k++] = src[(*i)++], k);
	if (src[*i + 1] == '?')
		return (check_interrogation(dst, i, last_exit_status));
	if (!ft_is_var_start(src[*i + 1]))
		return (dst[k++] = src[(*i)++], k);
	(*i)++;
	while (src[*i] && j < 255 && ft_is_var_char(src[*i]))
		var[j++] = src[(*i)++];
	var[j] = '\0';
	val = getenv(var);
	j = 0;
	if (val)
		while (val[j])
			dst[k++] = val[j++];
	return (k);
}

static char	*expand_str(const char *str, int last_exit_status)
{
	char	*res;
	int		len;

	len = 0;
	while (str[len])
		len++;
	res = malloc(len * 4 + 12);
	if (!res)
		return (NULL);
	quote_handling(str, res, last_exit_status);
	return (res);
}

void	ft_add_to_arr(char ***array, t_token *tok, int last_exit_status)
{
	const char	*to_add;
	int			len;
	char		**new_array;
	int			i;

	i = 0;
	len = get_array_len(*array);
	to_add = expand_str(tok->value, last_exit_status);
	if (!to_add || !to_add[0])
		return (free((char *)to_add));
	new_array = malloc(sizeof(char *) * (len + 2));
	if (!new_array)
		return ;
	while (i < len)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[len] = ft_strdup(to_add);
	new_array[len + 1] = NULL;
	free((char *)to_add);
	if (*array)
		free(*array);
	*array = new_array;
}
