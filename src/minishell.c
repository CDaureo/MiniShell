/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:20:29 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/04 11:40:03 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void minishell_init(t_ms *ms)
{
	ms->envp = NULL;
	ms->input = NULL;
	ms->prompt = "minishell>> ";
	ms->history = NULL;
	ms->cmd = NULL;
	ms->cmd_paths = NULL;
	ms->cmd_args = NULL;
	ms->exit_status = 0; 
	ms->fd[0] = -1;
	ms->fd[1] = -1;
	ms->pid = -1;
	// Initialize readline library

	while ((ms->input = readline("minishell>> ")))
	{
		if (ms->input[0] == '\0')
		{
			free(ms->input);
			continue;
		}	
		add_history(ms->input);
		free(ms->input);
    }
}
