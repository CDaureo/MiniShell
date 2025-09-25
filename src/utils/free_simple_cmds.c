/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_simple_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:16:05 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/25 15:28:42 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_simple_cmds(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;
	t_token			*redir_tmp;
	int				i;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->str)
		{
			i = 0;
			while (cmds->str[i])
			{
				free(cmds->str[i]);
				i++;
			}
			free(cmds->str);
		}
		while (cmds->redirections)
		{
			redir_tmp = cmds->redirections->next;
			free(cmds->redirections->value);
			free(cmds->redirections);
			cmds->redirections = redir_tmp;
		}
		if (cmds->hd_file_name)
		{
			unlink(cmds->hd_file_name);
			free(cmds->hd_file_name);
		}
		free(cmds);
		cmds = tmp;
	}
}
