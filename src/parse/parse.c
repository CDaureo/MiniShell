/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:12:56 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/24 13:12:54 by simgarci         ###   ########.fr       */
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
	printf("Creating a new simple command structure.\n");
	return (cmd);
}

void add_simple_cmd(t_simple_cmds **cmds, t_simple_cmds *new_cmd)
{
    t_simple_cmds *temp;

    // Print the command being added (all strings in the array)
    printf("Start Add: Adding command [");
    if (new_cmd->str)
    {
        for (int i = 0; new_cmd->str[i]; i++)
        {
            printf("'%s'", new_cmd->str[i]);
            if (new_cmd->str[i + 1])
                printf(", "); // Add a comma between arguments
        }
    }
    else
    {
        printf("Empty command");
    }
    printf("]\n");

    if (*cmds == NULL)
        *cmds = new_cmd;
    else
    {
        temp = *cmds;
        while (temp->next)
            temp = temp->next;
        temp->next = new_cmd;
    }

    // Confirm the command was added
    printf("End Add: Command added successfully\n");
}

//Esta hay que acortarla de columna y de lineas
void command_types(t_token **tokens, t_simple_cmds **cmds, t_simple_cmds *current_cmd, t_token *current_token)
{
    t_token *redir;
    t_token *prev_token = NULL;

    while (current_token)
    {
		if (current_cmd) {
			printf("Current command: %s\n", current_cmd->str ? current_cmd->str[0] : "NULL");
		} else {
			printf("Error: current_cmd is NULL\n");
		}
		if (current_token) {
			printf("Current token: ");
			printf("%s\n", current_token->value);
		} else {
			printf("Error: current_token is NULL\n");
		}
        if (current_token->type == TOKEN_PIPE)
        {
            // Add the current command to the list of commands
            add_simple_cmd(cmds, current_cmd);
            printf("Pipe detected. Starting a new command.\n");

            // Create a new command
            current_cmd = create_simple_cmd();

            // Update the token list
            if (prev_token)
                prev_token->next = current_token->next;
            free(current_token);
            current_token = prev_token ? prev_token->next : *tokens;
			printf("New command created, continuing with the next token.\n");
        }
		else if (current_token->type == TOKEN_APPEND || current_token->type == TOKEN_REDIRECT)
		{
			printf("Redirection token detected:");
			printf("%s\n", current_token->value);

			// Handle redirection
			redir = malloc(sizeof(t_token));
			if (redir)
			{
				*redir = *current_token;
				redir->next = current_cmd->redirections;
				current_cmd->redirections = redir;
				current_cmd->num_redirections++;
			}

			// Update the token list and free the current token
			t_token *temp = current_token;
			current_token = current_token->next;
			if (prev_token)
				prev_token->next = current_token;
			else
				*tokens = current_token;
			free(temp);
		}
		else
		{
			printf("String token detected:");
			printf( "'%s'\n", current_token->value);
			// Add the token to the current command's arguments
			ft_add_to_array(&current_cmd->str, current_token->value);
			printf("Added string '%s' to the current command.\n", current_token->value);

			// Free the current token and move to the next one
			t_token *temp = current_token;
			current_token = current_token->next;
			if (prev_token)
				prev_token->next = current_token;
			else
				*tokens = current_token;
			free(temp);
		}
    }
    // Add the last command to the list of commands
    if (current_cmd)
    {
        add_simple_cmd(cmds, current_cmd);
        printf("End of input. Adding the last command.\n");
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
