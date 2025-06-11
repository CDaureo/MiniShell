/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:08:09 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/11 13:00:46 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_envp(char **envp)
{
    int i = 0;
    while (envp[i])
        i++;
    return (i);
}

char *get_env_value(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

char **copy_envp(char **envp)
{
    int count = count_envp(envp);
    char **copy = malloc(sizeof(char *) * (count + 1));
    int i = 0;
    if (!copy)
        return NULL;
    while (i < count)
    {
        copy[i] = ft_strdup(envp[i]);
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return NULL;
        }
        i++;
    }
    copy[i] = NULL;
    return copy;
}

void update_env_var(t_env *env, const char *key, const char *value)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            free(env->value);
            env->value = ft_strdup(value);
            return;
        }
        env = env->next;
    }
}

t_env *init_env_list(char **envp)
{
    t_env *head = NULL;
    t_env *current = NULL;
    int i = 0;

    while (envp[i])
    {
        t_env *new = malloc(sizeof(t_env));
        if (!new)
            break;
        char *eq = ft_strchr(envp[i], '=');
        if (eq)
        {
            new->key = ft_strndup(envp[i], eq - envp[i]);
            new->value = ft_strdup(eq + 1);
        }
        else
        {
            new->key = ft_strdup(envp[i]);
            new->value = NULL;
        }
        new->next = NULL;
        if (!head)
            head = new;
        else
            current->next = new;
        current = new;
        i++;
    }
    return head;
}