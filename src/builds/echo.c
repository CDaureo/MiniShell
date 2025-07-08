/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:36:53 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/07/08 21:46:42 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_echo(char **argv)
{
    int i = 1;
    int line = 1;

    while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
    {
        line = 0;
        i++;
    }
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }
    if (line)
        printf("\n");
    return (0);
}
