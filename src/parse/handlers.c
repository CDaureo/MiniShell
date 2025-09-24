/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:00:31 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/22 16:01:08 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_append(t_append_args *args)
{
	append_token(args->tokens, create_token(args->type, args->value));
	*(args->i) += args->increment;
}

void	handle_pipes(int *i, t_token **tokens)
{
	append_token(tokens, create_token(TOKEN_PIPE, "|"));
	(*i)++;
}

static void	handle_redir_type(t_append_args *args, int type, const char *value,
	int increment)
{
	args->type = type;
	args->value = value;
	args->increment = increment;
	handle_append(args);
}

void	handle_redirections(const char *input, int *i, t_token **tokens)
{
	t_append_args	args;

	args.tokens = tokens;
	args.i = i;
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			handle_redir_type(&args, TOKEN_APPEND, ">>", 2);
		else
			handle_redir_type(&args, TOKEN_REDIRECT, ">", 1);
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			handle_redir_type(&args, TOKEN_HEREDOC, "<<", 2);
		else
			handle_redir_type(&args, TOKEN_INPUT, "<", 1);
	}
}

void	handle_words(const char *input, int *i, t_token **tokens)
{
	char	*buf;
	int		j;
	t_token	*tok;

	j = 0;
	buf = malloc(ft_strlen(input + *i) + 1);
	if (!buf)
		return ;
	while (input[*i] && !ft_is_word_delim(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
			j += append_quoted(buf + j, input, i);
		else
			buf[j++] = input[(*i)++];
	}
	buf[j] = '\0';
	tok = create_token(TOKEN_WORD, buf);
	tok->single_quoted = 0;
	append_token(tokens, tok);
	free(buf);
}
