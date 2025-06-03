/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:31:58 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/03 12:01:19 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *lexer(const char *input)
{
    t_token	*tokens;
	char	*word;
	int		i;
	int		start;

	tokens = NULL;
    i = 0;
    while (input[i])
    {
        if (ft_strchr(" \t\n\v\f\r", input[i]))
        {
            i++;
            continue;
        }
        if (input[i] == '|')
        {
            append_token(&tokens, create_token(TOKEN_PIPE, PIPE, "|"));
            i++;
        }
        else if (input[i] == '>')
        {
            if (input[i + 1] == '>')
            {
                append_token(&tokens, create_token(TOKEN_APPEND, GREAT_GREAT, ">>"));
                i += 2;
            }
            else
            {
                append_token(&tokens, create_token(TOKEN_REDIRECT, GREAT, ">"));
                i++;
            }
        }
        else if (input[i] == '<')
        {
            if (input[i + 1] == '<')
            {
                append_token(&tokens, create_token(TOKEN_REDIRECT, LESS_LESS, "<<"));
                i += 2;
            }
            else
            {
                append_token(&tokens, create_token(TOKEN_REDIRECT, LESS, "<"));
                i++;
            }
        }
        else
        {
            start = i;
            while (input[i] && !(ft_strchr(" \t\n\v\f\r", input[i])) && input[i] != '|' && input[i] != '>' && input[i] != '<')
                i++;
            word = strndup(&input[start], i - start);
            append_token(&tokens, create_token(TOKEN_WORD, 0, word));
            free(word);
        }
    }
    return tokens;
}
