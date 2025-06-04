/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:34:13 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/03 13:55:42 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Esta función convierte una lista de tokens en un array de strings
//para pasar directamente a execve.
static char **tokens_to_str(t_token *tokens)
{
	int count;
	int i;
	t_token *tkn = tokens;
	char **argv;
	count = 0;
	i = 0;
	// Contar cuántos tokens son de tipo TOKEN_WORD seguidos (hasta PIPE o NULL)
	while(tkn && tkn->type != TOKEN_PIPE)
	{
		if (tkn->type == TOKEN_WORD || tkn->type == TOKEN_REDIRECT || 
				tkn->type == TOKEN_APPEND)
			count++;
		tkn = tkn->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	tkn = tokens;
	while (i < count)
	{
		argv[i] = ft_strdup(tkn->value);
		tkn = tkn->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);	
}


