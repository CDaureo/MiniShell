/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaureo- <cdaureo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:18:06 by cdaureo-          #+#    #+#             */
/*   Updated: 2025/06/02 16:50:07 by cdaureo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;

	uc = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == uc)
		{
			return ((char *)(&s[i]));
		}
		else
			i++;
	}
	if (uc == '\0')
	{
		return ((char *)(&s[i]));
	}
	return (NULL);
}