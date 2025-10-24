/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:02:25 by lanton-m          #+#    #+#             */
/*   Updated: 2025/09/20 16:02:25 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	sup;

	if (!s1 || !set)
		return (0);
	while (*s1 != '\0' && ft_strchr(set, *s1))
		s1++;
	sup = ft_strlen(s1);
	while (sup && ft_strchr(set, s1[sup]))
		sup--;
	return (ft_substr(s1, 0, sup + 1));
}
