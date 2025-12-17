/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 12:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/12/16 13:18:10 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value, t_quote_type quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = NULL;
	token->quote = quote;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
			return (free(token), NULL);
	}
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	print_tokens(t_token *head)
{
	const char	*types[] = {"WORD", "PIPE", "<", ">", ">>", "<<"};

	while (head)
	{
		printf("[%s", types[head->type]);
		if (head->value)
			printf(":\"%s\"", head->value);
		printf("] ");
		head = head->next;
	}
	printf("\n");
}
