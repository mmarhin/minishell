/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:30:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/01/19 13:25:29 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_expanded_value(char *expanded);
void	free_split_words(char **words);

char	*join_and_free(char *s1, char *s2)
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

char	*process_quoted(char **input, t_shell *shell, int *has_quotes)
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

char	*process_unquoted(char **input, t_shell *shell)
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

int	is_only_var_expand(char *input)
{
	if (*input != '$')
		return (0);
	input++;
	if (*input == '?' || *input == '_' || ft_isalpha(*input))
	{
		if (*input == '?')
			input++;
		else
			while (ft_isalnum(*input) || *input == '_')
				input++;
		return (*input == '\0' || is_space(*input) || is_operator(*input));
	}
	return (0);
}

t_token	*handle_word(char **input, t_token *head, t_shell *shell)
{
	char	*expanded;
	char	**words;
	int		i;
	t_token	*tok;

	if (!is_only_var_expand(*input))
		return (handle_word_mixed(input, head, shell));
	expanded = process_unquoted(input, shell);
	if (!expanded)
		return (free_tokens(head), NULL);
	words = split_expanded_value(expanded);
	free(expanded);
	if (!words)
		return (free_tokens(head), NULL);
	i = 0;
	while (words[i])
	{
		tok = create_token(TOKEN_WORD, words[i], NO_QUOTE);
		if (!tok)
			return (free_split_words(words), free_tokens(head), NULL);
		add_token(&head, tok);
		i++;
	}
	free_split_words(words);
	return (head);
}
