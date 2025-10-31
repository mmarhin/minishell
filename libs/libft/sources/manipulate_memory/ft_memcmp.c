/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:58:03 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 15:58:03 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s_s1;
	const unsigned char	*s_s2;
	size_t				index;

	index = 0;
	s_s1 = (const unsigned char *)s1;
	s_s2 = (const unsigned char *)s2;
	while (index < n)
	{
		if (s_s1[index] != s_s2[index])
		{
			return (s_s1[index] - s_s2[index]);
		}
		index++;
	}
	return (0);
}
