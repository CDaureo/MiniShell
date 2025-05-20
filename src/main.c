/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:39:32 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/05/20 14:10:29 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
//un main de la minishell
 int main(void)
 {
 char *input;

    while ((input = readline("minishell> ")) != NULL)
    {
        if (*input)
            add_history(input); // Agrega el comando al historial

        if (strcmp(input, "clear_history") == 0)
            rl_clear_history(); // Limpia el historial si el usuario lo solicita

        free(input);
    }
	return(0);
 }