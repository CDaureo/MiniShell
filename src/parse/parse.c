/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:08:43 by simgarci          #+#    #+#             */
/*   Updated: 2025/09/25 16:33:17 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_simple_cmds	*create_simple_cmd(void)
{
	t_simple_cmds	*cmd;

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

void	add_simple_cmd(t_simple_cmds **cmds, t_simple_cmds *new_cmd)
{
	t_simple_cmds	*temp;

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

static void	command_types(t_simple_cmds **cmds, \
		t_simple_cmds **crnt_cmd, t_token **crnt_token, t_ms *ms)
{
	t_token	*tmp;

	if (!*crnt_token)
		return ;
	if ((*crnt_token)->type == TOKEN_PIPE)
	{
		add_simple_cmd(cmds, *crnt_cmd);
		*crnt_cmd = create_simple_cmd();
		tmp = *crnt_token;
		*crnt_token = (*crnt_token)->next;
		free_token_and_next(tmp, 0);
	}
	else if (
		(*crnt_token)->type == TOKEN_APPEND || \
		(*crnt_token)->type == TOKEN_REDIRECT || \
		(*crnt_token)->type == TOKEN_INPUT || \
		(*crnt_token)->type == TOKEN_HEREDOC)
		command_tokens(crnt_cmd, crnt_token);
	else
	{
		ft_add_to_arr(&(*crnt_cmd)->str, *crnt_token, ms->exit_status);
		tmp = *crnt_token;
		*crnt_token = (*crnt_token)->next;
		free_token_and_next(tmp, 0);
	}
}

void	parse_simple_cmds(t_token **tokens, t_simple_cmds **cmds, t_ms *ms)
{
	t_simple_cmds	*crnt_cmd;
	t_token			*crnt_token;

	crnt_cmd = create_simple_cmd();
	crnt_token = *tokens;
	while (crnt_token)
	{
		command_types(cmds, &crnt_cmd, &crnt_token, ms);
	}
	if (crnt_cmd->str || crnt_cmd->redirections)
		add_simple_cmd(cmds, crnt_cmd);
}
