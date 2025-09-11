/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_simple_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:16:05 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 18:16:37 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_simple_cmds(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;
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
		free(cmds);
		cmds = tmp;
	}
}
