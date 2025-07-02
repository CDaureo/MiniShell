/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuilds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:20:19 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/07/02 17:20:40 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_builtin(const char *cmd)
{
    if (!cmd)
        return 0;
    return (
        ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0
    );
}