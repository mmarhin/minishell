/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:02:04 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 16:02:04 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	indice;
	unsigned int	length;
	char			*str;

	length = ft_strlen(s);
	str = (char *)ft_calloc(length + 1, sizeof(char));
	if (!str)
		return (0);
	indice = 0;
	while (s[indice] != '\0')
	{
		str[indice] = (*f)(indice, s[indice]);
		indice++;
	}
	return (str);
}
