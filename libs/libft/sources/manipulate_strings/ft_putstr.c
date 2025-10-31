/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:01:18 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 16:01:20 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putstr(char *str)
{
	int	index;

	index = 0;
	if (!str)
		index = write(1, "(null)", 6);
	else
	{
		while (str[index] != '\0')
		{
			write (1, &str[index], 1);
			index++;
		}
	}
	return (index);
}
