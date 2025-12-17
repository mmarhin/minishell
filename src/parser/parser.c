/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:27:49 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/14 12:41:39 by mamarin-         ###   ########.fr       */
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
		return (shell->exit_status = 1, -1);
	redir->file = ft_strdup((*tokens)->value);
	if (!redir->file)
		return (free(redir), shell->exit_status = 1, -1);
	add_redir_to_cmd(cmd, redir);
	return (0);
}

static void	handle_pipe(t_cmd **first, t_cmd **last, t_cmd **current)
{
	if (!*first)
	{
		*first = *current;
		*last = *current;
	}
	else
	{
		(*last)->next = *current;
		*last = *current;
	}
	*current = cmd_init();
}

static int	check_pipe_start(t_token *tokens, t_shell *shell)
{
	if (!tokens || tokens->type == TOKEN_PIPE)
	{
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			ft_putendl_fd("minishell: syntax error near `|'", 2);
			shell->exit_status = 2;
		}
		return (1);
	}
	return (0);
}

static int	process_token(t_token **tk, t_cmd **cur, t_cmd **f, t_cmd **l)
{
	if ((*tk)->type == TOKEN_WORD)
		add_arg(*cur, *tk);
	else if ((*tk)->type == TOKEN_PIPE)
	{
		handle_pipe(f, l, cur);
		if (!*cur)
			return (-1);
	}
	return (0);
}

t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*first;
	t_cmd	*last;
	int		is_r;

	if (check_pipe_start(tokens, shell))
		return (NULL);
	first = NULL;
	last = NULL;
	current = cmd_init();
	if (!current)
		return (NULL);
	while (tokens)
	{
		is_r = is_redir(tokens->type);
		if (is_r && handle_redir(&tokens, current, shell) == -1)
			return (NULL);
		else if (!is_r && process_token(&tokens, &current, &first, &last) < 0)
			return (first);
		tokens = tokens->next;
	}
	if (!first)
		return (current);
	last->next = current;
	return (first);
}
