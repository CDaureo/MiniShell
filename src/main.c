///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   main.c                                             :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2025/05/20 13:39:32 by cdaureo-          #+#    #+#             */
///*   Updated: 2025/06/12 16:38:08 by simgarci         ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */

//#include "../includes/minishell.h"
//#include <unistd.h>   // getcwd, gethostname
//#include <pwd.h>      // getpwuid
//#include <sys/types.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

//int main(int argc, char **argv, char **envp)
//{
//    (void)argc;
//    (void)argv;
//    char *line;
//    t_token *tokens;
//    t_ms ms;
//    ms.envp = copy_envp(envp);
//    ms.env_list = init_env_list(envp);

//    char cwd[4096];
//    char hostname[256];
//    char *prompt;
//    char *user;
//    struct passwd *pw;

//    char *home_dir = getenv("HOME");
//    if (home_dir)
//        chdir(home_dir);

//    while (1)
//    {
//		pw = getpwuid(getuid());
//		if (pw && pw->pw_name)
//		    user = pw->pw_name;
//		else
//		    user = "user";

//        if (gethostname(hostname, sizeof(hostname)) != 0)
//            strcpy(hostname, "minishell");

//        if (!getcwd(cwd, sizeof(cwd)))
//            strcpy(cwd, "~");

//        // Obtener $HOME
//        char *home = getenv("HOME");
//        char *display_cwd = cwd;

//        // Si cwd empieza por $HOME, reemplaza por ~
//        if (home && strncmp(cwd, home, ft_strlen(home)) == 0)
//        {
//            // +1 para el slash final, si quieres ~/ en vez de solo ~
//            size_t home_len = ft_strlen(home);
//            size_t new_len = ft_strlen(cwd) - home_len + 2;
//            char *tmp = malloc(new_len);
//            if (tmp)
//            {
//                tmp[0] = '~';
//                strcpy(tmp + 1, cwd + home_len);
//                display_cwd = tmp;
//            }
//        }

//        size_t prompt_len = ft_strlen(user) + 1 + ft_strlen(hostname) + 1 + ft_strlen(display_cwd) + 3;
//        prompt = malloc(prompt_len);
//        if (!prompt)
//            prompt = strdup("$ ");
//        else
//            snprintf(prompt, prompt_len, "%s@%s:%s$ ", user, hostname, display_cwd);

//        line = readline(prompt);
//        free(prompt);
//        if (display_cwd != cwd)
//            free(display_cwd);
//        if (!line)
//            break;
//        if (*line)
//        {
//            add_history(line);
//            tokens = lexer(line);
//            if (tokens)
//            {
//                char **argv_cmd = tokens_to_str(tokens);
//                int has_pipe = 0;
//                t_token *tmp = tokens;
//                while (tmp)
//                {
//                    if (tmp->type == TOKEN_PIPE)
//                    {
//                        has_pipe = 1;
//                        break;
//                    }
//                    tmp = tmp->next;
//                }
//                if (has_pipe)
//                    execute_pipeline(tokens, envp, &ms);
//                else
//                    handle_builds(argv_cmd, &ms);
//                ft_free_split(argv_cmd);
//                free_tokens(tokens);
//            }
//        }
//        free(line);
//    }
//    return 0;
//}
#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

// Assuming these functions and structs are defined elsewhere
t_token *lexer(const char *input);
void parse_simple_cmds(t_token **tokens, t_simple_cmds **cmds);
void free_tokens(t_token *tokens);
void free_simple_cmds(t_simple_cmds *cmds);

// Updated helper function to print simple commands
void print_simple_cmds(t_simple_cmds *cmds)
{
    t_simple_cmds *current = cmds;
    while (current)
    {
        // Print command tokens (array of arrays)
        printf("Command:\n");
        for (int i = 0; current->str && current->str[i]; i++)
        {
            printf("  Token[%d]: %s\n", i, current->str[i]);
        }

        // Print redirections (t_token struct)
        if (current->redirections)
        {
            printf("Redirections:\n");
            t_token *redir = current->redirections;
            while (redir)
            {
                printf("  Type: %d, Value: %s\n", redir->type, redir->value);
                redir = redir->next;
            }
        }

        current = current->next;
    }
}
/*
int main(void)
{
    const char *input = "echo Hello World > output.txt";
    t_token *tokens = NULL;
    t_simple_cmds *cmds = NULL;
	printf("Paso 1\n");
    // Step 1: Generate tokens using the lexer
    tokens = lexer(input);
    if (!tokens)
    {
        fprintf(stderr, "Lexer failed to generate tokens.\n");
        return EXIT_FAILURE;
    }
	printf("Paso 2\n");
    // Step 2: Parse tokens into simple commands
    parse_simple_cmds(&tokens, &cmds);
    if (!cmds)
    {
        fprintf(stderr, "Parsing failed to generate commands.\n");
        return EXIT_FAILURE;
    }
	printf("Paso 3\n");
    // Step 3: Print the resulting command list
    print_simple_cmds(cmds);

    // Free allocated memory
    //free_tokens(tokens);
    //free_simple_cmds(cmds);

    return EXIT_SUCCESS;
}
*/