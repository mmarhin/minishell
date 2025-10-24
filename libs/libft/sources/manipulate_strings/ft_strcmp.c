/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:26:01 by lanton-m          #+#    #+#             */
/*   Updated: 2025/10/24 10:26:01 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int ft_strcmp(const char *a, const char *b)
{
    size_t i;
	
	i = 0;
    while (a[i] && a[i]==b[i]) 
		i++;
    return (unsigned char)a[i] - (unsigned char)b[i];
}
