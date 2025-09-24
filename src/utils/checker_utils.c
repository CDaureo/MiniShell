/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:00:00 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/22 16:08:07 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_array_len(char **array)
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

int	ft_is_var_start(char c)
{
	return (c == '_' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_is_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || \
			(c >= 'a' && c <= 'z') || \
			(c >= '0' && c <= '9') || \
			c == '_');
}

int	ft_is_word_delim(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' \
		|| c == '\f' || c == '\r' || c == '|' || c == '>' || c == '<');
}

int	append_quoted(char *dst, const char *src, int *i)
{
	int		k;
	char	q;

	k = 0;
	q = src[*i];
	dst[k++] = src[(*i)++];
	while (src[*i] && src[*i] != q)
		dst[k++] = src[(*i)++];
	if (src[*i] == q)
	{
		dst[k++] = src[(*i)++];
	}
	return (k);
}
