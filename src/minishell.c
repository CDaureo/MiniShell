/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:20:29 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/17 01:01:54 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell_init(t_ms *ms)
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
}
