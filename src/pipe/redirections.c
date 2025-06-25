/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:20:04 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/25 18:33:17 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../../includes/minishell.h"

void apply_redirections(t_simple_cmds *cmd)
{
    t_token *redir = cmd->redirections;
    int fd;

    while (redir)
    {
        if (redir->type == TOKEN_REDIRECT) // >
        {
            fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == TOKEN_APPEND) // >>
        {
            fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        // Puedes añadir aquí manejo para < y << si lo necesitas
        printf("Redirigiendo tipo %d a archivo %s\n", redir->type, redir->value);
        redir = redir->next;
    }
}