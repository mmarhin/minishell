/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:10:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/11/16 17:18:13 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_spaces(char **str)
{
	while (**str && is_space(**str))
		(*str)++;
}

char	*extract_word(char **str)
{
	char	*start;
	int		len;
	char	*word;

	start = *str;
	len = 0;
	while ((*str)[len] && !is_space((*str)[len]) && !is_operator((*str)[len]))
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	*str += len;
	return (word);
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

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
