/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   handlers.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cdaureo- <cdaureo-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/11 18:04:20 by cdaureo-		  #+#	#+#			 */
/*   Updated: 2025/09/17 00:56:45 by cdaureo-		 ###   ########.fr	   */
/*																			*/
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
	int				start;
	char			*word;
	t_quote			qr;
	int				single_quoted;
	t_token			*tok;

	single_quoted = 0;
	start = *i;
	if (input[*i] == '\'' || input[*i] == '"')
	{
		qr = handle_quotes(input, i);
		word = qr.word;
		single_quoted = qr.single_quoted;
	}
	else
	{
		while (input[*i] && !(ft_strchr(" \t\n\v\f\r", input[*i])) \
			&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
			(*i)++;
		word = ft_strndup(&input[start], *i - start);
	}
	tok = create_token(TOKEN_WORD, word);
	tok->single_quoted = single_quoted;
	append_token(tokens, tok);
	free(word);
}
