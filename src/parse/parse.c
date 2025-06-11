/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:12:56 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/11 15:35:59 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_simple_cmds *create_simple_cmd(void)
{
	t_simple_cmds *cmd;

	cmd = malloc(sizeof(t_simple_cmds));
	if (!cmd)
		return (NULL);
	cmd->str = NULL;
	cmd->builtin = NULL;
	cmd->num_redirections = 0;
	cmd->hd_file_name = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

void add_simple_cmd(t_simple_cmds **cmds, t_simple_cmds *new_cmd)
{
	t_simple_cmds *temp;
	
	if (*cmds == NULL)
		*cmds = new_cmd;
	else
	{
		temp = *cmds;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
	}
}

void command_types(t_token **tokens, t_simple_cmds **cmds, t_simple_cmds *current_cmd, t_token *current_token)
{
	t_token *redir;
	t_token *prev_token;
	
	prev_token = NULL;
	redir = malloc(sizeof(t_token));

	if (current_token->type == TOKEN_PIPE)
	{
		add_simple_cmd(cmds, current_cmd);
		current_cmd = create_simple_cmd();
		if (prev_token)
			prev_token->next = current_token->next; // Remove pipe token
		free(current_token);
		current_token = prev_token ? prev_token->next : *tokens;
	}
	else
	{
		if (current_token->type == TOKEN_APPEND || current_token->type == TOKEN_REDIRECT)
		{
			redir = malloc(sizeof(t_token));
			if (redir)
			{
				*redir = *current_token; // Copy token data
				redir->next = current_cmd->redirections;
				current_cmd->redirections = redir;
				current_cmd->num_redirections++;
			}
		}
		else if (current_token->type == TOKEN_WORD)
			ft_add_to_array(&current_cmd->str, current_token->value);
		prev_token = current_token;
		current_token = current_token->next;
	}	
}

void parse_simple_cmds(t_token **tokens, t_simple_cmds **cmds)
{
	t_simple_cmds *current_cmd;
	t_token *current_token;
	
	current_cmd = create_simple_cmd();
	current_token = *tokens;
	while (current_token)
	{
		command_types(tokens, cmds, current_cmd, current_token);
	}
	if (current_cmd->str || current_cmd->redirections)
		add_simple_cmd(cmds, current_cmd);
}
