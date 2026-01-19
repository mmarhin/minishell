/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/01/19 14:00:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	collapse_loop(char *str, char *dst)
{
	int	in_space;

	in_space = 1;
	while (*str)
	{
		if (*str == ' ' || *str == '\t' || *str == '\n')
		{
			if (!in_space)
				*dst++ = ' ';
			in_space = 1;
		}
		else
		{
			*dst++ = *str;
			in_space = 0;
		}
		str++;
	}
	if (dst > dst - 1 && *(dst - 1) == ' ')
		dst--;
	*dst = '\0';
}

char	*collapse_spaces(char *str)
{
	char	*result;
	char	*start;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	start = result;
	collapse_loop(str, result);
	return (start);
}
