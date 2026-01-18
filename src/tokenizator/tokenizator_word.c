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

static char	*process_quoted(char **input, t_shell *shell, int *has_quotes)
{
	char			*content;
	char			*expanded;
	t_quote_type	type;
	int				is_dollar_quote;

	is_dollar_quote = (**input == '$');
	if (is_dollar_quote)
		(*input)++;
	type = NO_QUOTE;
	content = extract_quoted_string(input, &type);
	if (!content)
		return (NULL);
	*has_quotes = 1;
	if (type == DOUBLE_QUOTE)
	{
		expanded = expand_string(content, shell, DOUBLE_QUOTE);
		free(content);
		return (expanded);
	}
	return (content);
}

static char	*process_unquoted(char **input, t_shell *shell)
{
	char	*word;
	char	*expanded;

	word = extract_word(input);
	if (!word)
		return (NULL);
	expanded = expand_string(word, shell, NO_QUOTE);
	free(word);
	return (expanded);
}

static char	*build_token_value(char **input, t_shell *shell, int *has_quotes)
{
	char	*result;
	char	*segment;

	result = NULL;
	*has_quotes = 0;
	while (**input && !is_space(**input) && !is_operator(**input))
	{
		if (**input == '$' && ((*input)[1] == '"' || (*input)[1] == '\''))
			segment = process_quoted(input, shell, has_quotes);
		else if (is_quote(**input))
			segment = process_quoted(input, shell, has_quotes);
		else
			segment = process_unquoted(input, shell);
		result = join_and_free(result, segment);
		if (!result)
			return (NULL);
	}
	return (result);
}

t_token	*handle_word(char **input, t_token *head, t_shell *shell)
{
	char			*value;
	t_token			*new_token;
	t_quote_type	quote_type;
	int				has_quotes;

	value = build_token_value(input, shell, &has_quotes);
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
