/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:00:00 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/17 13:21:00 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (args)
	{
		while (args[count])
			count++;
	}
	return (count);
}

void	add_arg(t_shell *shell, t_cmd *aux, t_token *tokens)
{
	char	**new_args;
	int		i;
	int		count;

	count = count_args(aux->args);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < count)
	{
		new_args[i] = aux->args[i];
		i++;
	}
	new_args[count] = expand_string(tokens->value, shell, tokens->quote);
	if (!new_args[count])
		return (free(new_args));
	new_args[count + 1] = NULL;
	if (aux->args)
		free(aux->args);
	aux->args = new_args;
}
