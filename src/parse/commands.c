/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:09:18 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/16 13:19:25 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token_and_next(t_token *tok, int free_next)
{
	if (!tok)
		return ;
	if (tok->value)
		free(tok->value);
	if (free_next && tok->next)
	{
		if (tok->next->value)
			free(tok->next->value);
		free(tok->next);
	}
	free(tok);
}

void	command_tokens(t_simple_cmds **current_cmd, t_token **current_token)
{
	t_token	*redir;
	t_token	*tmp;

	if ((*current_token)->next)
	{
		redir = malloc(sizeof(t_token));
		if (redir)
		{
			redir->type = (*current_token)->type;
			redir->value = ft_strdup((*current_token)->next->value);
			redir->next = (*current_cmd)->redirections;
			(*current_cmd)->redirections = redir;
			(*current_cmd)->num_redirections++;
		}
		tmp = *current_token;
		*current_token = (*current_token)->next->next;
		free_token_and_next(tmp, 1);
	}
	else
	{
		tmp = *current_token;
		*current_token = (*current_token)->next;
		free_token_and_next(tmp, 0);
	}
}
