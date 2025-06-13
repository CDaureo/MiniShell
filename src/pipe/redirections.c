/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:20:04 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/12 17:44:17 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void apply_redirections(t_simple_cmds *cmd)
{
    t_token *tmp = cmd->redirections; // Accede a la lista de redirecciones del comando
    int fd;

    while (tmp)
    {
        if ((tmp->type == TOKEN_APPEND || tmp->specific == GREAT_GREAT) && tmp->value)
        {
            fd = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror("minishell: redirection");
                _exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("minishell: dup2");
                close(fd);
                _exit(1);
            }
            close(fd);
        }
        else if ((tmp->type == TOKEN_REDIRECT || tmp->specific == GREAT) && tmp->value)
        {
            fd = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("minishell: redirection");
                _exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("minishell: dup2");
                close(fd);
                _exit(1);
            }
            close(fd);
        }
        else if ((tmp->type == TOKEN_REDIRECT || tmp->specific == LESS) && tmp->value)
        {
            fd = open(tmp->value, O_RDONLY);
            if (fd < 0)
            {
                perror("minishell: redirection");
                _exit(1);
            }
            if (dup2(fd, STDIN_FILENO) < 0)
            {
                perror("minishell: dup2");
                close(fd);
                _exit(1);
            }
            close(fd);
        }
        tmp = tmp->next;
    }
}