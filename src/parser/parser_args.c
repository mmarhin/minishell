/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:00:00 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 16:20:58 by mamarin-         ###   ########.fr       */
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

static char	**create_new_args(t_cmd *aux, char *expanded)
{
	char	**new_args;
	int		i;
	int		count;

	count = count_args(aux->args);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (free(expanded), NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = aux->args[i];
		i++;
	}
	new_args[count] = expanded;
	new_args[count + 1] = NULL;
	return (new_args);
}

void	add_arg(t_shell *shell, t_cmd *aux, t_token *tokens)
{
	char	**new_args;
	char	*expanded;

	(void)shell;
	expanded = ft_strdup(tokens->value);
	if (!expanded)
		return ;
	if (expanded[0] == '\0' && tokens->quote == NO_QUOTE)
		return (free(expanded));
	new_args = create_new_args(aux, expanded);
	if (!new_args)
		return ;
	if (aux->args)
		free(aux->args);
	aux->args = new_args;
}

t_parse_ctx	ctx_init(t_shell *shell)
{
	t_parse_ctx	aux;

	aux.first = NULL;
	aux.last = NULL;
	aux.shell = shell;
	return (aux);
}
