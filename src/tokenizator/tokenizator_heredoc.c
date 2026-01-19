/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/01/19 12:48:01 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s2)
		return (free(s1), NULL);
	if (!s1)
		return (s2);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*extract_raw_quoted(char **input, int *has_quotes)
{
	char	*content;
	char	quote;
	char	*chr;

	quote = **input;
	(*input)++;
	content = ft_strdup("");
	while (**input && **input != quote)
	{
		chr = ft_substr(*input, 0, 1);
		content = join_and_free(content, chr);
		(*input)++;
	}
	if (**input == quote)
		(*input)++;
	*has_quotes = 1;
	return (content);
}

static char	*extract_raw_char(char **input)
{
	char	*segment;

	segment = ft_substr(*input, 0, 1);
	(*input)++;
	return (segment);
}

static char	*build_raw_value(char **input, int *has_quotes)
{
	char	*result;
	char	*segment;

	result = NULL;
	*has_quotes = 0;
	while (**input && !is_space(**input) && !is_operator(**input))
	{
		if (**input == '$' && ((*input)[1] == '"' || (*input)[1] == '\''))
			(*input)++;
		if (is_quote(**input))
			segment = extract_raw_quoted(input, has_quotes);
		else
			segment = extract_raw_char(input);
		result = join_and_free(result, segment);
		if (!result)
			return (NULL);
	}
	return (result);
}

t_token	*handle_heredoc_delim(char **input, t_token *head)
{
	char			*value;
	t_token			*new_token;
	t_quote_type	quote_type;
	int				has_quotes;

	value = build_raw_value(input, &has_quotes);
	if (!value)
		return (free_tokens(head), NULL);
	if (has_quotes)
		quote_type = MIXED_QUOTE;
	else
		quote_type = NO_QUOTE;
	new_token = create_token(TOKEN_WORD, value, quote_type);
	free(value);
	if (!new_token)
		return (free_tokens(head), NULL);
	add_token(&head, new_token);
	return (head);
}
