/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 21:59:48 by lanton-m          #+#    #+#             */
/*   Updated: 2026/01/19 12:22:14 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*aux;

	aux = malloc(sizeof(t_cmd));
	if (!aux)
		return (NULL);
	aux->args = NULL;
	aux->next = NULL;
	aux->redirs = NULL;
	return (aux);
}

t_redir	*redir_init(t_token_type type)
{
	t_redir	*aux;

	aux = malloc(sizeof(t_redir));
	if (!aux)
		return (NULL);
	aux->file = NULL;
	aux->heredoc_content = NULL;
	aux->next = NULL;
	aux->type = type;
	return (aux);
}

void	add_redir_to_cmd(t_cmd *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	current = cmd->redirs;
	while (current->next)
		current = current->next;
	current->next = redir;
}

int	is_redir(t_token_type type)
{
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND
		|| type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT)
		return (1);
	return (0);
}

int	check_pipe_start(t_token *tokens, t_shell *shell)
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
