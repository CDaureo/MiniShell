#include "../../includes/minishell.h"

void free_simple_cmds(t_simple_cmds *cmds)
{
    t_simple_cmds *tmp;

    while (cmds)
    {
        tmp = cmds->next;
        printf("Liberando comando...\n");
        if (cmds->str)
        {
            for (int i = 0; cmds->str[i]; i++) {
                printf("  Liberando arg: %s\n", cmds->str[i]);
                free(cmds->str[i]);
            }
            printf("  Liberando array de argumentos\n");
            free(cmds->str);
        }
        // Si tienes redirecciones, pon prints aquí también
        // printf("  Liberando redirecciones\n");
        // free_redirections(cmds->redirections);
        printf("  Liberando estructura comando\n");
        free(cmds);
        cmds = tmp;
    }
    printf("Fin de free_simple_cmds\n");
}