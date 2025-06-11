/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:39:32 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/11 13:10:02 by cdaureo-         ###   ########.fr       */
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
    ms.envp = copy_envp(envp);
    ms.env_list = init_env_list(envp); // <-- Añade esta línea

    char cwd[4096];
    char hostname[256];
    char *prompt;
    char *user;
    struct passwd *pw;

    while (1)
    {
		pw = getpwuid(getuid());
		if (pw && pw->pw_name)
		    user = pw->pw_name;
		else
		    user = "user";

        if (gethostname(hostname, sizeof(hostname)) != 0)
            strcpy(hostname, "minishell");

        if (!getcwd(cwd, sizeof(cwd)))
            strcpy(cwd, "~");

        // Obtener $HOME
        char *home = getenv("HOME");
        char *display_cwd = cwd;

        // Si cwd empieza por $HOME, reemplaza por ~
        if (home && strncmp(cwd, home, strlen(home)) == 0)
        {
            // +1 para el slash final, si quieres ~/ en vez de solo ~
            size_t home_len = strlen(home);
            size_t new_len = strlen(cwd) - home_len + 2;
            char *tmp = malloc(new_len);
            if (tmp)
            {
                tmp[0] = '~';
                strcpy(tmp + 1, cwd + home_len);
                display_cwd = tmp;
            }
        }

        size_t prompt_len = strlen(user) + 1 + strlen(hostname) + 1 + strlen(display_cwd) + 3;
        prompt = malloc(prompt_len);
        if (!prompt)
            prompt = strdup("$ ");
        else
            snprintf(prompt, prompt_len, "%s@%s:%s$ ", user, hostname, display_cwd);

        line = readline(prompt);
        free(prompt);
        if (display_cwd != cwd)
            free(display_cwd);
        if (!line)
            break;
        if (*line)
        {
            add_history(line);
            tokens = lexer(line);
            if (tokens)
            {
                char **argv_cmd = tokens_to_str(tokens);
                int has_pipe = 0;
                t_token *tmp = tokens;
                while (tmp)
                {
                    if (tmp->type == TOKEN_PIPE)
                    {
                        has_pipe = 1;
                        break;
                    }
                    tmp = tmp->next;
                }
                if (has_pipe)
                    execute_pipeline(tokens, envp, &ms);
                else
                    handle_builds(argv_cmd, &ms);
                ft_free_split(argv_cmd);
                free_tokens(tokens);
            }
        }
        free(line);
    }
    return 0;
}
