/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:41:47 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/10 16:28:46 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_builds(char **argv, t_ms *ms)
{

	if (ft_strcmp(argv[0], "cd") == 0)
		return(ms->exit_status = ft_cd(argv, ms->envp), 1);
	
	return(0);
}