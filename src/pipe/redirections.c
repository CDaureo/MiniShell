/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:20:04 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/07/01 18:41:11 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../../includes/minishell.h"

void apply_redirections(t_simple_cmds *cmd, t_ms *ms)
{
    t_token *redir = cmd->redirections;
    int fd;

    while (redir)
    {
        if (redir->type == TOKEN_REDIRECT) // >
        {
            fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror(redir->value);
                ms->exit_status = 1;
                return;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == TOKEN_APPEND) // >>
        {
            fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
            {
                perror(redir->value);
                ms->exit_status = 1;
                return;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type == TOKEN_INPUT) // <
        {
            fd = open(redir->value, O_RDONLY);
            if (fd < 0)
            {
                perror(redir->value);
                ms->exit_status = 1;
                return;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (redir->type == TOKEN_HEREDOC) // <<
        {
            fd = open(redir->value, O_RDONLY);
            if (fd < 0)
            {
                perror(redir->value);
                ms->exit_status = 1;
                return;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        redir = redir->next;
    }
}