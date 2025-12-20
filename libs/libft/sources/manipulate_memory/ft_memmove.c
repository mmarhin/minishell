/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:58:13 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 15:58:13 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*source;
	char	*destiny;
	size_t	index;

	source = (char *)src;
	destiny = (char *)dest;
	index = 0;
	if (source > destiny)
	{
		while (index < len)
		{
			destiny[index] = source[index];
			index++;
		}
	}
	else
	{
		while (index != len)
		{
			destiny[len - index - 1] = source[len - index - 1];
			index++;
		}
	}
	return (dest);
}
