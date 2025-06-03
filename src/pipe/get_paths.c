/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:18:40 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/03 13:32:50 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_cmd_path(char *cmd, char **envp)
{
	int i = 0;
	int j = 0;
	char **paths;
	char *full_path;
	char *tmp;

	    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);
        else
            return NULL;
    }
	
	// Buscar PATH en envp
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return NULL;

	// Separar PATH en rutas
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return NULL;

	while (paths[j])
	{
		tmp = ft_strjoin(paths[j], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths); // Libera el array de strings
			return full_path;
		}
		free(full_path);
		j++;
	}
	ft_free_split(paths);
	return NULL;
}

/*
int main(int argc, char **argv, char **envp)
{
	char *cmd_path;
	char *cmd;

	if (argc != 2)
	{
		printf("Uso: %s <comando>\n", argv[0]);
		return (1);
	}
	cmd = argv[1];
	cmd_path = get_cmd_path(cmd, envp);
	if (cmd_path)
	{
		printf("Ruta encontrada: %s\n", cmd_path);
		free(cmd_path);
	}
	else
	{
		printf("Comando '%s' no encontrado en PATH\n", cmd);
	}
	return (0);
}
*/