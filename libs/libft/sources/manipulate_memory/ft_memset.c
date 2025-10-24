/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:58:18 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 15:58:18 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			index;
	unsigned char	*ptr;

	ptr = str;
	index = 0;
	while (index < len)
	{
		ptr[index] = (unsigned char)c;
		index++;
	}
	return (str);
}
