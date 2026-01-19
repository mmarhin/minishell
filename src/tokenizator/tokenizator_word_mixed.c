/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_word_mixed.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/01/19 13:25:29 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *s1, char *s2);
char	*process_quoted(char **input, t_shell *shell, int *has_quotes);
char	*process_unquoted(char **input, t_shell *shell);
char	*collapse_spaces(char *str);

static int	has_unquoted_var(char *input)
{
	char	quote;

	while (*input && !is_space(*input) && !is_operator(*input))
	{
		if (*input == '"' || *input == '\'')
		{
			quote = *input++;
			while (*input && *input != quote)
				input++;
			if (*input)
				input++;
		}
		else if (*input == '$' && (ft_isalpha(input[1]) || input[1] == '_'))
			return (1);
		else
			input++;
	}
	return (0);
}

static char	*get_segment(char **input, t_shell *shell, int *hq)
{
	if (**input == '$' && ((*input)[1] == '"' || (*input)[1] == '\''))
		return (process_quoted(input, shell, hq));
	else if (is_quote(**input))
		return (process_quoted(input, shell, hq));
	return (process_unquoted(input, shell));
}

static char	*build_mixed_value(char **input, t_shell *shell, int *hq)
{
	char	*result;
	char	*seg;

	result = ft_strdup("");
	while (**input && !is_space(**input) && !is_operator(**input))
	{
		seg = get_segment(input, shell, hq);
		result = join_and_free(result, seg);
		if (!result)
			return (NULL);
	}
	return (result);
}

static t_token	*add_word_token(t_token *head, char *value)
{
	t_token	*tok;

	tok = create_token(TOKEN_WORD, value, MIXED_QUOTE);
	free(value);
	if (!tok)
		return (free_tokens(head), NULL);
	add_token(&head, tok);
	return (head);
}

t_token	*handle_word_mixed(char **input, t_token *head, t_shell *shell)
{
	char	*value;
	char	*collapsed;
	int		hq;
	int		needs_collapse;

	hq = 0;
	needs_collapse = has_unquoted_var(*input);
	value = build_mixed_value(input, shell, &hq);
	if (!value)
		return (free_tokens(head), NULL);
	if (!needs_collapse)
		return (add_word_token(head, value));
	collapsed = collapse_spaces(value);
	free(value);
	if (!collapsed)
		return (free_tokens(head), NULL);
	return (add_word_token(head, collapsed));
}
