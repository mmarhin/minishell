/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:30:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/12/20 12:01:41 by lanton-m         ###   ########.fr       */
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

static void	update_quote_type(t_quote_type *quote, t_quote_type tmp_quote)
{
	if (*quote == NO_QUOTE)
		*quote = tmp_quote;
	else if (*quote != tmp_quote)
		*quote = MIXED_QUOTE;
}

static char	*handle_quoted_segment(char **input, char *result,
		t_quote_type *quote, int skip_dollar)
{
	char			*segment;
	t_quote_type	tmp_quote;

	if (skip_dollar)
		(*input)++;
	tmp_quote = NO_QUOTE;
	segment = extract_quoted_string(input, &tmp_quote);
	update_quote_type(quote, tmp_quote);
	result = append_segment(result, segment);
	return (result);
}

static char	*build_word(char **input, t_quote_type *quote)
{
	char	*result;
	char	*segment;

	result = NULL;
	*quote = NO_QUOTE;
	while (**input && !is_space(**input) && !is_operator(**input))
	{
		if (**input == '$' && ((*input)[1] == '"' || (*input)[1] == '\''))
			result = handle_quoted_segment(input, result, quote, 1);
		else if (is_quote(**input))
			result = handle_quoted_segment(input, result, quote, 0);
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
