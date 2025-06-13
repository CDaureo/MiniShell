/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:06:39 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/12 17:10:44 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_append(t_token **tokens, int type, int subtype, const char *value, int *i, int increment)
{
	append_token(tokens, create_token(type, subtype, value));
	*i += increment;
}

void	handle_pipes(int *i, t_token **tokens)
{
	append_token(tokens, create_token(TOKEN_PIPE, PIPE, "|"));
	(*i)++;
}

void	handle_redirections(const char *input, int *i, t_token **tokens)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			handle_append(tokens, TOKEN_APPEND, GREAT_GREAT, ">>", i, 2);
		else
			handle_append(tokens, TOKEN_APPEND, GREAT, ">", i, 2);
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')              
			handle_append(tokens, TOKEN_APPEND, LESS_LESS, "<<", i, 2);
		else
			handle_append(tokens, TOKEN_APPEND, LESS, "<", i, 2);
	}
}

static char	*handle_quotes(const char *input, int *i)
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
	{
		fprintf(stderr, "Error: Unmatched %c quote\n", quote); //cambiar por version ft
		return (NULL);
	}
	word = ft_strndup(&input[start], *i - start);
	(*i)++;
	return (word);
}

void	handle_words(const char *input, int *i, t_token **tokens)
{
	int		start;
	char	*word;
	
	start = *i;
	if (input[*i] == '\'' || input[*i] == '"')
		word = handle_quotes(input, i);
	else
	{
		while (input[*i] && !(ft_strchr(" \t\n\v\f\r", input[*i])) \
			&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
			(*i)++;
		word = ft_strndup(&input[start], *i - start);
	}
	append_token(tokens, create_token(TOKEN_WORD, 0, word));
	free(word);
}
