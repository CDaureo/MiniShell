/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:22:21 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/12 15:32:17 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_pwd(void)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)))
		return (printf("%s\n", cwd), 0);
	else
		return (1);
}
