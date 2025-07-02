/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:39:32 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/07/02 16:58:15 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>   // getcwd, gethostname
#include <pwd.h>      // getpwuid
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *line;
    t_token *tokens;
    t_ms ms;

    char cwd[4096];
    char hostname[256];
    char *prompt;
    char *user;
    struct passwd *pw;


    ms.envp = copy_envp(envp);
    ms.env_list = init_env_list(envp);
	setup_signals();
    while (1)
    {
        pw = getpwuid(getuid());
        if (pw && pw->pw_name)
            user = pw->pw_name;
        else
            user = "user";

        if (gethostname(hostname, sizeof(hostname)) != 0)
            ft_strcpy(hostname, "minishell");

        char *pwd_env = get_env_value(ms.env_list, "PWD");
        if (pwd_env)
            ft_strlcpy(cwd, pwd_env, sizeof(cwd));
        else if (!getcwd(cwd, sizeof(cwd)))
            ft_strcpy(cwd, "~");

        char *home = getenv("HOME");
        char *display_cwd = cwd;
        int display_malloced = 0;

        if ((home && ft_strcmp(cwd, home) == 0))
        {
            display_cwd = "~";
            display_malloced = 0;
        }
        else if (home)
        {
            size_t home_len = ft_strlen(home);
            if (ft_strncmp(cwd, home, home_len) == 0 && cwd[home_len] == '/')
            {
                size_t new_len = ft_strlen(cwd) - home_len + 2;
                char *tmp = malloc(new_len);
                if (tmp)
                {
                    tmp[0] = '~';
                    ft_strcpy(tmp + 1, cwd + home_len);
                    display_cwd = tmp;
                    display_malloced = 1;
                }
            }
        }

        size_t prompt_len = ft_strlen(user) + 1 + ft_strlen(hostname) + 1 + ft_strlen(display_cwd) + 3;
        prompt = malloc(prompt_len);
        if (!prompt)
            prompt = strdup("$ ");
        else
            snprintf(prompt, prompt_len, "%s@%s:%s$ ", user, hostname, display_cwd);

        line = readline(prompt);
        free(prompt);
        // Solo liberar si display_cwd fue malloc'd
        if (display_malloced)
            free(display_cwd);
        if (!line)
            break;
        if (*line)
        {
            add_history(line);
            tokens = lexer(line);
            if (tokens)
            {
                t_simple_cmds *cmds = NULL;
                parse_simple_cmds(&tokens, &cmds, &ms);

                if (cmds && cmds->next)
                    execute_pipeline(cmds, envp, &ms);
                else if (cmds)
                {
                    pid_t pid = fork();
                    if (pid == 0)
                    {
                        apply_redirections(cmds, &ms);
                        handle_builds(cmds->str, &ms);
                    }
                    else if (pid > 0)
                    {
                        int status;
                        waitpid(pid, &status, 0);
                        // Actualiza exit_status si quieres
                    }
                }
                t_simple_cmds *tmp = cmds;
                int n = 1;
                while (tmp)
                {
                    printf("CMD %d:\n", n++);
                    for (int i = 0; tmp->str && tmp->str[i]; i++)
                        printf("  ARG[%d]: %s\n", i, tmp->str[i]);
                    for (t_token *r = tmp->redirections; r; r = r->next)
                        printf("  REDIR: type=%d, value=%s\n", r->type, r->value);
                    tmp = tmp->next;
                }
                free_simple_cmds(cmds);
                printf("Comandos liberados\n");
            }
        }
    }
    return 0;
}