/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:36:53 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/13 16:48:53 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_echo(char **argv)
{
	int i;
	int line;

	i = 1;
	line = 1;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		line = 0; // Si hay -n, no se imprime el salto de línea
		i++;
	}
	    // Imprimir los argumentos
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i + 1]) // Si hay más argumentos, imprimir un espacio
            printf(" ");
        i++;
    }
	if (line)
        printf("\n");
	return (0);
}