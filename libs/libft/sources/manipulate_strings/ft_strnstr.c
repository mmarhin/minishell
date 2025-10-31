/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:02:14 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 16:02:14 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	sup;

	if (ft_strlen(little) == 0)
	{
		return ((char *)big);
	}
	index = 0;
	while (big[index] != '\0' && index < len)
	{
		sup = 0;
		while ((big[index + sup] == little[sup]) && (index + sup) < len)
		{
			if (little[sup + 1] == '\0')
				return ((char *)&big[index]);
			sup++;
		}
		index++;
	}
	return (NULL);
}
