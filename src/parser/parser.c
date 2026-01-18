/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:27:49 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 15:32:26 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_heredoc_content(char *delim, t_shell *shell, t_quote_type qt)
{
	char	*content;
	char	*line;
	char	*tmp;
	size_t	len;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (1)
	{
		if (shell->interactive)
			line = readline("> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (!shell->interactive && len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (qt == NO_QUOTE)
		{
			tmp = expand_string(line, shell, DOUBLE_QUOTE);
			free(line);
			line = tmp;
		}
		tmp = ft_strjoin(content, line);
		free(content);
		free(line);
		content = ft_strjoin(tmp, "\n");
		free(tmp);
		if (!content)
			return (NULL);
	}
	return (content);
}

static int	handle_redir(t_token **tokens, t_cmd *cmd, t_shell *shell)
{
	t_redir			*redir;
	t_token_type	redir_type;
	t_quote_type	quote_type;

	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		shell->exit_status = 2;
		return (-1);
	}
	quote_type = (*tokens)->quote;
	redir = redir_init(redir_type);
	if (!redir)
		return (shell->exit_status = 1, -1);
	redir->file = expand_string((*tokens)->value, shell, quote_type);
	if (!redir->file)
		return (free(redir), shell->exit_status = 1, -1);
	if (redir_type == TOKEN_HEREDOC)
	{
		redir->heredoc_content = read_heredoc_content(redir->file, shell,
				quote_type);
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
	ctx.first = NULL;
	ctx.last = NULL;
	ctx.shell = shell;
	current = cmd_init();
	if (!current)
		return (NULL);
	while (tokens)
	{
		is_r = is_redir(tokens->type);
		if (is_r && handle_redir(&tokens, current, shell) == -1)
			return (NULL);
		else if (!is_r && process_token(&tokens, &current, &ctx) < 0)
			return (ctx.first);
		tokens = tokens->next;
	}
	if (!ctx.first)
		return (current);
	ctx.last->next = current;
	return (ctx.first);
}
