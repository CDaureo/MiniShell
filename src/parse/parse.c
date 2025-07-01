/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:12:56 by simgarci          #+#    #+#             */
/*   Updated: 2025/07/01 14:12:32 by simgarci         ###   ########.fr       */
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

    printf("Start Add: Adding command [");
    if (new_cmd->str)
    {
        for (int i = 0; new_cmd->str[i]; i++)
        {
            printf("'%s'", new_cmd->str[i]);
            if (new_cmd->str[i + 1])
                printf(", ");
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

    printf("End Add: Command added successfully\n");
}

//Esta hay que acortarla de columna y de lineas
void command_types(t_token **tokens, t_simple_cmds **cmds, t_simple_cmds **current_cmd, t_token **current_token, t_ms *ms)
{
    t_token *redir;
    t_token *tmp;
    (void)tokens;
    if (!*current_token)
        return;

    if ((*current_token)->type == TOKEN_PIPE)
    {
        add_simple_cmd(cmds, *current_cmd);
        *current_cmd = create_simple_cmd();
        tmp = *current_token;
        *current_token = (*current_token)->next;
        free(tmp->value);
        free(tmp);
    }
    else if (
        (*current_token)->type == TOKEN_APPEND ||
        (*current_token)->type == TOKEN_REDIRECT ||
        (*current_token)->type == TOKEN_INPUT ||
        (*current_token)->type == TOKEN_HEREDOC)
    {
        // Verifica que hay un token siguiente (el archivo)
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
            // Libera ambos tokens
            tmp = *current_token;
            *current_token = (*current_token)->next->next;
            free(tmp->next->value);
            free(tmp->next);
            free(tmp->value);
            free(tmp);
        }
        else
        {
            // Error: redirección sin archivo
            tmp = *current_token;
            *current_token = (*current_token)->next;
            free(tmp->value);
            free(tmp);
        }
    }
    else
    {
        ft_add_to_array(&(*current_cmd)->str, (*current_token)->value, ms->exit_status);
        tmp = *current_token;
        *current_token = (*current_token)->next;
        free(tmp->value);
        free(tmp);
    }
}

void parse_simple_cmds(t_token **tokens, t_simple_cmds **cmds, t_ms *ms)
{
	t_simple_cmds *current_cmd;
	t_token *current_token;
	
	current_cmd = create_simple_cmd();
	current_token = *tokens;
	while (current_token)
	{
		command_types(tokens, cmds, &current_cmd, &current_token, ms);
	}
	if (current_cmd->str || current_cmd->redirections)
		add_simple_cmd(cmds, current_cmd);
}
