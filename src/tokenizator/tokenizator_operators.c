/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator_operators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:10:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/12/19 16:21:34 by mamarin-         ###   ########.fr       */
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
	return (create_token(type, NULL, NO_QUOTE));
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
	return (create_token(type, NULL, NO_QUOTE));
}

t_token	*create_operator_token(char **str)
{
	if (**str == '|')
	{
		(*str)++;
		return (create_token(TOKEN_PIPE, NULL, NO_QUOTE));
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
