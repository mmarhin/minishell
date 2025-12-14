/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:00:00 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/14 12:27:33 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quoted_string(char **str)
{
	char	quote;
	char	*start;
	int		len;
	char	*result;

	quote = **str;
	(*str)++;
	start = *str;
	len = 0;
	while ((*str)[len] && (*str)[len] != quote)
		len++;
	if ((*str)[len] != quote)
		return (NULL);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);
	*str += len + 1;
	return (result);
}
