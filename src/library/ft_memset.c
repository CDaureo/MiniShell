/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:24:35 by simgarci          #+#    #+#             */
/*   Updated: 2024/10/01 12:47:50 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, int n)
{
	int				i;
	unsigned char	car;

	i = 0;
	car = (unsigned char)c;
	while (i < n)
	{
		((unsigned char *)str)[i] = car;
		i++;
	}
	return (str);
}
