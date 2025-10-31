/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:57:26 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 15:57:28 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		count += ft_putchar('-');
		count += ft_putchar('2');
		count += ft_putnbr(147483648);
	}
	else if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
		count += ft_putnbr(nb);
	}
	else if (nb > 9)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putnbr(nb % 10);
	}
	else
		count += ft_putchar(nb + 48);
	return (count);
}

int	ft_putnbr_unsigned(unsigned int number)
{
	unsigned int	nbr;

	nbr = 0;
	if (number <= 9)
		return (ft_putchar((number + 48)));
	else
	{
		nbr += ft_putnbr_unsigned(number / 10);
		nbr += ft_putchar((number % 10) + 48);
	}
	return (nbr);
}
