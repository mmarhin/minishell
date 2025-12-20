/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 21:59:48 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/14 12:26:00 by mamarin-         ###   ########.fr       */
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
