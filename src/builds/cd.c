/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:35:59 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/05 17:25:41 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_cd(char **argv, char **envp)
{
	(void)envp;
	
	// Esto es si no pasa la ruta a la que quiere ir
	if (!argv[1])
	{
		char *home = getenv("home");
		if (!home)
			return(error_msg("cd: HOME not set"), 1);
		if (chdir(home) != 0) //CHDIR cambia de directorio
			return(error_msg("cd"), 1);
		return (0);
	}
	// Esto es si pasa la ruta ir a esa ruta
		if (chdir(argv[1]) != 0)
			return(error_msg("cd"), 1);
	return(0);
}