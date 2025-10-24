/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:57:57 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 15:57:57 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			index;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (str[index] == ch)
		{
			return ((void *)s + index);
		}
		index++;
	}
	return (NULL);
}
