/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:26:35 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/05/29 19:26:47 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dupe;
	size_t	size;

	i = 0;
	size = ft_strlen((char *)s);
	dupe = malloc(size + 1 * sizeof(char));
	if (dupe == NULL)
	{
		return (NULL);
	}
	while (i < size)
	{
		dupe[i] = s[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}