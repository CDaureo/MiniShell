/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:08:58 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/16 14:42:00 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_input(const char *input, int i)
{
	if (input[i] == '|' || input[i] == '>' || input[i] == '<')
	{
		if (input[i + 1] && (input[i + 1] == '>' || input[i + 1] == '<'))
			return (1);
	}
	else if (ft_strchr(" \t\n\v\f\r", input[i]))
		return (0);
	return (1);
}

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->single_quoted = 0;
	token->next = NULL;
	return (token);
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		printf("Liberando token: %s\n", tokens->value);
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
	printf("Fin de free_tokens\n");
}

t_token	*lexer(const char *input)
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
			continue ;
		}
		if (!check_input(input, i))
			return (NULL);
		if (input[i] == '|')
			handle_pipes(&i, &tokens);
		else if (input[i] == '>' || input[i] == '<')
			handle_redirections(input, &i, &tokens);
		else
			handle_words(input, &i, &tokens);
	}
	return (tokens);
}
