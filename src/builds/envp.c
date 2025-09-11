/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:06:29 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 16:26:10 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_existing_var(t_env *tmp, const char *value)
{
	free(tmp->value);
	if (value != NULL)
		tmp->value = ft_strdup(value);
	else
		tmp->value = NULL;
}

static void	add_new_var(t_env *tmp, const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value != NULL)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (tmp)
		tmp->next = new;
}

void	update_env_var(t_env *env_list, const char *key, const char *value)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			update_existing_var(tmp, value);
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	add_new_var(tmp, key, value);
}

static t_env	*create_env_node(const char *env_var)
{
	t_env	*new;
	char	*eq;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	eq = ft_strchr(env_var, '=');
	if (eq)
	{
		new->key = ft_strndup(env_var, eq - env_var);
		new->value = ft_strdup(eq + 1);
	}
	else
	{
		new->key = ft_strdup(env_var);
		new->value = NULL;
	}
	new->next = NULL;
	return (new);
}

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new;
	int		i;

	i = 0;
	current = NULL;
	head = NULL;
	while (envp[i])
	{
		new = create_env_node(envp[i]);
		if (!new)
			break ;
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	return (head);
}
