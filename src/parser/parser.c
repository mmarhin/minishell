/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:27:49 by lanton-m          #+#    #+#             */
/*   Updated: 2026/01/19 11:27:43 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_heredoc_content(char *delim, t_shell *shell, t_quote_type qt);
int		check_pipe_start(t_token *tokens, t_shell *shell);

static int	check_token_word(t_token **tk, t_shell *shell)
{
	*tk = (*tk)->next;
	if (!*tk || (*tk)->type != TOKEN_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		shell->exit_status = 2;
		return (-1);
	}
	return (0);
}

static int	handle_redir(t_token **tk, t_cmd *cmd, t_shell *shell)
{
	t_redir			*redir;
	t_token_type	rtype;
	t_quote_type	qtype;

	rtype = (*tk)->type;
	if (check_token_word(tk, shell) < 0)
		return (-1);
	qtype = (*tk)->quote;
	redir = redir_init(rtype);
	if (!redir)
		return (shell->exit_status = 1, -1);
	redir->file = expand_string((*tk)->value, shell, qtype);
	if (!redir->file)
		return (free(redir), shell->exit_status = 1, -1);
	if (rtype == TOKEN_HEREDOC)
	{
		redir->heredoc_content = read_heredoc_content(redir->file, shell,
				qtype);
		if (!redir->heredoc_content)
			return (free(redir->file), free(redir), shell->exit_status = 1, -1);
	}
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

static int	process_token(t_token **tk, t_cmd **cur, t_parse_ctx *ctx)
{
	if ((*tk)->type == TOKEN_WORD)
		add_arg(ctx->shell, *cur, *tk);
	else if ((*tk)->type == TOKEN_PIPE)
	{
		handle_pipe(&ctx->first, &ctx->last, cur);
		if (!*cur)
			return (-1);
	}
	return (0);
}

t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd		*current;
	t_parse_ctx	ctx;
	int			is_r;

	if (check_pipe_start(tokens, shell))
		return (NULL);
	ctx = (t_parse_ctx){NULL, NULL, shell};
	current = cmd_init();
	if (!current)
		return (NULL);
	while (tokens)
	{
		is_r = is_redir(tokens->type);
		if (is_r && handle_redir(&tokens, current, shell) == -1)
			return (free_cmd_list(current), free_cmd_list(ctx.first), NULL);
		else if (!is_r && process_token(&tokens, &current, &ctx) < 0)
			return (free_cmd_list(current), ctx.first);
		tokens = tokens->next;
	}
	if (!ctx.first)
		return (current);
	ctx.last->next = current;
	return (ctx.first);
}
