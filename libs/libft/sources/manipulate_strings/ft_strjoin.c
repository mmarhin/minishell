/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:01:41 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 16:01:41 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	len_s1 = 0;
	while (s1[len_s1] != '\0')
	{
		str[len_s1] = s1[len_s1];
		len_s1++;
	}
	len_s2 = 0;
	while (s2[len_s2] != '\0')
	{
		str[len_s1 + len_s2] = s2[len_s2];
		len_s2++;
	}
	str[len_s1 + len_s2] = '\0';
	return (str);
}
