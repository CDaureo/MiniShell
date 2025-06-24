#include "../../includes/minishell.h"

void free_simple_cmds(t_simple_cmds *cmds)
{
    t_simple_cmds *tmp;

    while (cmds)
    {
        tmp = cmds;
        cmds = cmds->next;

        // Liberar el array de argumentos
        if (tmp->str)
            ft_free_split(tmp->str);

        // Liberar la lista de redirecciones
        t_token *redir = tmp->redirections;
        while (redir)
        {
            t_token *next_redir = redir->next;
            if (redir->value)
                free(redir->value);
            free(redir);
            redir = next_redir;
        }

        // Liberar el nombre del archivo heredoc si existe
        if (tmp->hd_file_name)
            free(tmp->hd_file_name);

        // Liberar la estructura del comando
        free(tmp);
    }
}