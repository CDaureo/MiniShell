/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:58:09 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/25 12:22:08 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quote	handle_quotes(const char *input, int *i)
{
	int		start;
	char	quote;
	t_quote	res;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	res.word = ft_strndup(&input[start - 1], (*i - start) + 2);
	res.single_quoted = (quote == '\'');
	if (input[*i] == quote)
		(*i)++;
	else
	{
		ft_putstr_fd("Error: Unmatched ", 2);
		write(2, &quote, 1);
		ft_putendl_fd(" quote", 2);
	}
	return (res);
}

int	handle_single_quote(char *dst, const char *src, int *i)
{
	int	k;

	k = 0;
	(*i)++;
	while (src[*i] && src[*i] != '\'')
		dst[k++] = src[(*i)++];
	if (src[*i] == '\'')
		(*i)++;
	return (k);
}

int	handle_double_quote(char *dst, const char *src, int *i, \
	int last_exit_status)
{
	int	k;

	k = 0;
	(*i)++;
	while (src[*i] && src[*i] != '"')
	{
		if (src[*i] == '$')
			k += copy_var_value(dst + k, src, i, last_exit_status);
		else
			dst[k++] = src[(*i)++];
	}
	if (src[*i] == '"')
		(*i)++;
	return (k);
}
