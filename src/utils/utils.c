/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:32:31 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/03 12:40:03 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void pipex(t_ms *ms)
{
	pid_t pid;
	if(pipe(ms->fd) == -1)
		error_msg("error creating pipe");
	pid = fork();
	if (pid < 0)
	{
		error_msg("error creating child process");
		return;
	}
}