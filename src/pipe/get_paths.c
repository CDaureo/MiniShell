/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_paths.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: cdaureo- <cdaureo-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/03 13:18:40 by cdaureo-		  #+#	#+#			 */
/*   Updated: 2025/07/04 17:34:10 by cdaureo-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
	}
	if (!envp[i])
		return (-1);
	return (i);
}

static char	**get_paths_array(char **envp)
{
	int		index;
	char	**paths;

	index = find_path_index(envp);
	if (index == -1)
		return (NULL);
	paths = ft_split(envp[index] + 5, ':');
	return (paths);
}

static char	*try_paths(char **paths, char *cmd)
{
	int		j;
	char	*tmp;
	char	*full_path;

	j = 0;
	while (paths[j])
	{
		tmp = ft_strjoin(paths[j], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		j++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_paths_array(envp);
	if (!paths)
		return (NULL);
	full_path = try_paths(paths, cmd);
	ft_free_split(paths);
	return (full_path);
}
