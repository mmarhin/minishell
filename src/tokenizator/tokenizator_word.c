/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:30:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/12/19 16:21:33 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_segment(char *result, char *segment)
{
	char	*new_result;

	if (!segment)
		return (free(result), NULL);
	if (!result)
		return (segment);
	new_result = ft_strjoin(result, segment);
	free(result);
	free(segment);
	return (new_result);
}

static char	*build_word(char **input, t_quote_type *quote)
{
	char	*result;
	char	*segment;

	result = NULL;
	while (**input && !is_space(**input) && !is_operator(**input))
	{
		if (is_quote(**input))
		{
			segment = extract_quoted_string(input, quote);
			result = append_segment(result, segment);
		}
		else
		{
			segment = extract_word(input);
			result = append_segment(result, segment);
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

t_token	*handle_word(char **input, t_token *head)
{
	char			*result;
	t_token			*new_token;
	t_quote_type	quote;

	quote = NO_QUOTE;
	result = build_word(input, &quote);
	if (!result)
		return (free_tokens(head), NULL);
	new_token = create_token(TOKEN_WORD, result, quote);
	free(result);
	if (!new_token)
		return (free_tokens(head), NULL);
	add_token(&head, new_token);
	return (head);
}
