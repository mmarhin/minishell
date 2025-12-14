/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_operators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:10:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/12/14 12:18:01 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*handle_redir_in(char **str)
{
	t_token_type	type;

	(*str)++;
	if (**str == '<')
	{
		(*str)++;
		type = TOKEN_HEREDOC;
	}
	else
		type = TOKEN_REDIR_IN;
	return (create_token(type, NULL));
}

static t_token	*handle_redir_out(char **str)
{
	t_token_type	type;

	(*str)++;
	if (**str == '>')
	{
		(*str)++;
		type = TOKEN_REDIR_APPEND;
	}
	else
		type = TOKEN_REDIR_OUT;
	return (create_token(type, NULL));
}

t_token	*create_operator_token(char **str)
{
	if (**str == '|')
	{
		(*str)++;
		return (create_token(TOKEN_PIPE, NULL));
	}
	if (**str == '<')
		return (handle_redir_in(str));
	if (**str == '>')
		return (handle_redir_out(str));
	return (NULL);
}

t_token	*handle_operator(char **input, t_token *head)
{
	t_token	*new_token;

	new_token = create_operator_token(input);
	if (!new_token)
		return (free_tokens(head), NULL);
	add_token(&head, new_token);
	return (head);
}

t_token	*handle_word(char **input, t_token *head)
{
	char	*word;
	t_token	*new_token;

	if (is_quote(**input))
		word = extract_quoted_string(input);
	else
		word = extract_word(input);
	if (!word)
		return (free_tokens(head), NULL);
	new_token = create_token(TOKEN_WORD, word);
	free(word);
	if (!new_token)
		return (free_tokens(head), NULL);
	add_token(&head, new_token);
	return (head);
}
