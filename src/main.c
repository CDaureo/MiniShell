/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:39:32 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/04 14:02:08 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *line;
    t_token *tokens;

    while ((line = readline("minishell>> ")))
    {
        if (*line)
        {
            add_history(line);
            tokens = lexer(line); // Usa tu lexer de token_helpers.c
            if (tokens)
            {
                execute_pipeline(tokens, envp); // Usa tu función de pipex.c
                free_tokens(tokens);            // Libera memoria de tokens
            }
        }
        free(line);
    }
    return 0;
}
 