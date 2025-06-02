/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:39:32 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/02 16:42:44 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//un main de la minishell
int main(int argc, char **argv, char **envp)
{	
	(void)argc;
	(void)argv;
 	t_ms t_ms;
	t_ms.envp = envp;
	minishell_init(&t_ms);
	return(0);
 }