/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:34:13 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/07/02 17:00:54 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_command_in_pipeline(
    t_simple_cmds *cmd, int previous_fd, int *fd, char **envp, t_ms *ms)
{
    if (fd) // Si hay siguiente comando, redirige stdout al pipe
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
    if (previous_fd != -1) // Si hay anterior, redirige stdin al pipe anterior
    {
        dup2(previous_fd, STDIN_FILENO);
        close(previous_fd);
    }
    // Aplica redirecciones del comando
    apply_redirections(cmd, ms);

    // Ejecuta builtins en el hijo si están en una tubería
    if (cmd->str && handle_builds(cmd->str, ms))
        exit(0);

    // Antes de buscar el path o ejecutar el comando
    if (!cmd->str || !cmd->str[0])
        exit(0); // O return, según el contexto

    char *path = get_cmd_path(cmd->str[0], envp);
    if (path)
    {
        execve(path, cmd->str, envp);
        free(path);
    }
    error_msg(cmd->str[0]);
    exit(1);
}

void execute_pipeline(t_simple_cmds *cmds, char **envp, t_ms *ms)
{
    pid_t pid;
    int previous_fd = -1;
    int fd[2];
    t_simple_cmds *cmd = cmds;

    while (cmd)
    {
        if (cmd->next)
            pipe(fd);
        else
            fd[0] = fd[1] = -1;

        pid = fork();
        if (pid < 0)
            error_msg("Error al crear el proceso hijo");
        if (pid == 0)
            run_command_in_pipeline(cmd, previous_fd, cmd->next ? fd : NULL, envp, ms);

        if (previous_fd != -1)
            close(previous_fd);
        if (cmd->next)
        {
            close(fd[1]);
            previous_fd = fd[0];
        }
        cmd = cmd->next;
    }
    while (wait(NULL) != -1)
        ;
}
