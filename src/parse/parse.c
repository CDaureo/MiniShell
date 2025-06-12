/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:12:56 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/12 17:27:01 by simgarci         ###   ########.fr       */
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

//Esta hay que acortarla de columna y de lineas
void command_types(t_token **tokens, t_simple_cmds **cmds, t_simple_cmds *current_cmd, t_token *current_token)
{
    t_token *redir;
    t_token *prev_token = NULL;

    while (current_token)
    {
        if (current_token->type == TOKEN_PIPE)
        {
            // Finalize the current command and add it to the list
            add_simple_cmd(cmds, current_cmd);
            current_cmd = create_simple_cmd(); // Start a new command
            if (prev_token)
                prev_token->next = current_token->next;
            free(current_token);
            current_token = prev_token ? prev_token->next : *tokens;
        }
        else if (current_token->type == TOKEN_APPEND || current_token->type == TOKEN_REDIRECT)
        {
            // Handle redirection
            redir = malloc(sizeof(t_token));
            if (redir)
            {
                *redir = *current_token;
                redir->next = current_cmd->redirections;
                current_cmd->redirections = redir;
                current_cmd->num_redirections++;
            }
            prev_token = current_token;
            current_token = current_token->next;
        }
        else if (current_token->type == TOKEN_WORD)
        {
            // Add word to the command's str array
            ft_add_to_array(&current_cmd->str, current_token->value);
            prev_token = current_token;
            current_token = current_token->next;
        }
        else
        {
            // Move to the next token for unhandled cases
            prev_token = current_token;
            current_token = current_token->next;
        }
    }

    // Add the last command to the list
    if (current_cmd)
        add_simple_cmd(cmds, current_cmd);
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
