/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:06:39 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/03 13:07:24 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void append_redirection_token(t_token **tokens, int type, int subtype, const char *value, int *i, int increment)
{
    append_token(tokens, create_token(type, subtype, value));
    *i += increment;
}

static void	handle_pipes(const char *input, int *i, t_token **tokens)
{
	append_token(tokens, create_token(TOKEN_PIPE, PIPE, "|"));
	(*i)++;
}

static void	handle_redirections(const char *input, int *i, t_token **tokens)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			append_redirection_token(tokens, TOKEN_APPEND, GREAT_GREAT, ">>", i, 2);
		else
			append_redirection_token(tokens, TOKEN_APPEND, GREAT, ">", i, 2);
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			append_redirection_token(tokens, TOKEN_APPEND, LESS_LESS, "<<", i, 2);
		else
			append_redirection_token(tokens, TOKEN_APPEND, LESS, "<", i, 2);
	}
}

static void	handle_words(const char *input, int *i, t_token **tokens)
{
	int		start;
	char	*word;
	
	start = *i;
	while (input[*i] && !(ft_strchr(" \t\n\v\f\r", input[*i])) && input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
		*i++;
	word = strndup(&input[start], i - start);
	append_token(&tokens, create_token(TOKEN_WORD, 0, word));
	free(word);
}

t_token *lexer(const char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_strchr(" \t\n\v\f\r", input[i]))
		{
			i++;
			continue;
		}
		if(!check_input(input, i))
			return (NULL);
		if (input[i] == '|')
			handle_pipes(input, &i, &tokens);
		else if (input[i] == '>' || input[i] == '<')
			handle_redirections(input, &i, &tokens);
		else
			handle_word(input, &i, &tokens);
	}
	return (tokens);
}
