/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:08:41 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 18:16:46 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_quotes(const char *input, int *i)
{
	int		start;
	char	quote;
	char	*word;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		fprintf(stderr, "Error: Unmatched %c quote\n", quote);
	word = ft_strndup(&input[start], *i - start);
	(*i)++;
	return (word);
}
