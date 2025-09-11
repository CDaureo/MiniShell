/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:06:03 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/09/11 16:27:52 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	line;

	i = 1;
	line = 1;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		line = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (line)
		printf("\n");
	return (0);
}
