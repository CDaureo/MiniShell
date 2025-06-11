/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:12:56 by simgarci          #+#    #+#             */
/*   Updated: 2025/06/11 12:44:56 by cdaureo-         ###   ########.fr       */
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

void parse_simple_cmds(t_token **tokens, t_simple_cmds **cmds)
{
	t_simple_cmds *current_cmd;
	//t_token *prev_token;
	t_token *current_token;
	
	current_cmd = create_simple_cmd();
	//prev_token = NULL;
	current_token = *tokens;
	while (current_token)
	{
		command_types(tokens, cmds, current_cmd, current_token);

	}
	if (current_cmd->str || current_cmd->redirections)
		add_simple_cmd(cmds, current_cmd);
}

char	**ft_add_to_array(char **array, const char *str)
{
    int		len = 0;
    char	**new_array;

    if (array)
    {
        while (array[len])
            len++;
    }
    new_array = malloc(sizeof(char *) * (len + 2));
    if (!new_array)
        return (NULL);
    for (int i = 0; i < len; i++)
        new_array[i] = array[i];
    new_array[len] = ft_strdup(str);
    new_array[len + 1] = NULL;
    free(array);
    return (new_array);
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
			current_cmd->str = ft_add_to_array(current_cmd->str, current_token->value);
		prev_token = current_token;
		current_token = current_token->next;
	}	
}
