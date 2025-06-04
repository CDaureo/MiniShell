/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:49:25 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/04 15:51:01 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char *ft_strndup(const char *s, size_t n)
{
	size_t len = 0;
	char *dup;

	while (s[len] && len < n)
		len++;

	dup = (char *)malloc(len + 1);
	if (!dup)
		return NULL;

	size_t i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}

	dup[len] = '\0';
	return dup;
}