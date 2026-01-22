/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 12:47:23 by mamarin-          #+#    #+#             */
/*   Updated: 2026/01/19 12:30:48 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_heredoc_pending(t_token *head)
{
	t_token	*last;

	if (!head)
		return (0);
	last = head;
	while (last->next)
		last = last->next;
	return (last->type == TOKEN_HEREDOC);
}

t_token	*tokenize(char *input, t_shell *shell)
{
	t_token	*head;

	head = NULL;
	while (*input)
	{
		skip_spaces(&input);
		if (!*input)
			break ;
		if (is_operator(*input))
			head = handle_operator(&input, head);
		else if (is_heredoc_pending(head))
			head = handle_heredoc_delim(&input, head);
		else
			head = handle_word(&input, head, shell);
		if (!head)
			return (NULL);
	}
	return (head);
}
