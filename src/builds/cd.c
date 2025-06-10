/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:35:59 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/10 16:14:19 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>

int ft_cd(char **argv, char **envp)
{
    (void)envp;
    char *dir;

    if (!argv[1])
    {
        dir = getenv("HOME");
        if (!dir)
        {
            ft_putendl_fd("cd: HOME not set", 2);
            return (1);
        }
    }
    else
        dir = argv[1];

    if (chdir(dir) != 0)
    {
        fprintf(stderr, "cd: %s: ", dir);
        perror("");
        return (1);
    }
    return (0);
}