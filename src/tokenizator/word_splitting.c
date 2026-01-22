/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/01/19 13:25:29 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
		{
			if (!in_word)
				count++;
			in_word = 1;
		}
		else
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*extract_next_word(char **str)
{
	char	*start;
	char	*word;
	int		len;

	while (**str && (**str == ' ' || **str == '\t' || **str == '\n'))
		(*str)++;
	if (!**str)
		return (NULL);
	start = *str;
	len = 0;
	while (**str && **str != ' ' && **str != '\t' && **str != '\n')
	{
		len++;
		(*str)++;
	}
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static void	free_partial_words(char **words, int i)
{
	while (--i >= 0)
		free(words[i]);
	free(words);
}

char	**split_expanded_value(char *expanded)
{
	char	**words;
	char	*ptr;
	int		count;
	int		i;

	if (!expanded)
		return (NULL);
	count = count_words(expanded);
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	ptr = expanded;
	i = -1;
	while (++i < count)
	{
		words[i] = extract_next_word(&ptr);
		if (!words[i])
			return (free_partial_words(words, i), NULL);
	}
	words[count] = NULL;
	return (words);
}

void	free_split_words(char **words)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}
