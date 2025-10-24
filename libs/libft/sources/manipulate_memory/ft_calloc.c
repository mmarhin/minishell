/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:57:52 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 15:57:52 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	if (nitems * size == 0 || nitems > 2147483647 / size)
		return (NULL);
	ptr = malloc(nitems * size);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, nitems * size);
	return (ptr);
}
