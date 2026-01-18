/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 12:47:23 by mamarin-          #+#    #+#             */
/*   Updated: 2025/11/16 13:13:11 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else
			head = handle_word(&input, head, shell);
		if (!head)
			return (NULL);
	}
	return (head);
}
