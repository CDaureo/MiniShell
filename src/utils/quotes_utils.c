/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:08:41 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/16 14:22:50 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quote_result	handle_quotes(const char *input, int *i)
{
	int		start;
	char	quote;
	t_quote_result	res;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	res.word = ft_strndup(&input[start], *i - start);
	res.single_quoted = (quote == '\'');
	if (input[*i] == quote)
		(*i)++;
	else
		fprintf(stderr, "Error: Unmatched %c quote\n", quote);
	return (res);
}
