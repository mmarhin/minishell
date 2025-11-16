/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:27:49 by lanton-m          #+#    #+#             */
/*   Updated: 2025/11/16 17:27:49 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redir(t_token **tokens, t_cmd *cmd, t_shell *shell)
{
	t_redir			*redir;
	t_token_type	redir_type;

	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		shell->exit_status = 2;
		return (-1);
	}
	redir = redir_init(redir_type);
	if (!redir)
	{
		shell->exit_status = 1;
		return (-1);
	}
	redir->file = ft_strdup((*tokens)->value);
	if (!redir->file)
	{
		free(redir);
		shell->exit_status = 1;
		return (-1);
	}
	add_redir_to_cmd(cmd, redir);
	return (0);
}

t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*first;
	t_cmd	*last;

	if (!tokens || tokens->type == TOKEN_PIPE)
	{
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
			shell->exit_status = 2;
		}
		return (NULL);
	}
	first = NULL;
	last = NULL;
	current = cmd_init();
	if (!current)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			add_arg(current, tokens);
		else if (tokens->type == TOKEN_PIPE)
		{
			if (!first)
			{
				first = current;
				last = current;
			}
			else
			{
				last->next = current;
				last = current;
			}
			current = cmd_init();
			if (!current)
				return (first);
		}
		else if (is_redir(tokens->type))
		{
			if (handle_redir(&tokens, current, shell) == -1)
				return (NULL);
		}
		tokens = tokens->next;
	}
	if (!first)
		first = current;
	else
		last->next = current;
	return (first);
}