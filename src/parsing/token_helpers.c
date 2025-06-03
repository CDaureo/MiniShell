/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:40:08 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/03 13:10:22 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(const char *input, int i)
{
	if (input[i] == '|' || input[i] == '>' || input[i] == '<')
	{
		if (input[i + 1] && (input[i + 1] == '|' || input[i + 1] == '>' || input[i + 1] == '<'))
			return (0);
	}
	else if (ft_strchr(" \t\n\v\f\r", input[i]))
		return (0);
	return (1);
}

t_token *create_token(t_token_type type, t_tokens specific, const char *value)
{
    t_token *token;

	token = malloc(sizeof(t_token));
	
    if (!token)
        return NULL;
    token->type = type;
    token->specific = specific;
	if (value)
		token->value = ft_strdup(value);
	else 
		token->value = NULL;
    token->next = NULL;
    return token;
}

void append_token(t_token **head, t_token *new_token)
{
    t_token *current;
	
    if (!*head)
    {
        *head = new_token;
        return;
    }
	current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

void free_tokens(t_token *tokens)
{
    t_token	*current;
	t_token	*next;
	
	current = tokens;
    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

//int main()
//{
//    const char *input = "ls | grep foo < output.txt";
//    t_token *tokens = lexer(input);

//    // Print tokens
//    t_token *current = tokens;
//    while (current)
//    {
//        printf("Type: %d, Specific: %d, Value: %s\n", current->type, current->specific, current->value);
//        current = current->next;
//    }

//    // Free tokens
//    free_tokens(tokens);
//    return 0;
//}
