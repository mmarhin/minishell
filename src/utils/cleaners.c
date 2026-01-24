/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:12:46 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/14 12:27:45 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freesplit(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_environ(char **envp)
{
	ft_freesplit(envp);
}

static void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		if (redirs->file)
			free(redirs->file);
		if (redirs->heredoc_content)
			free(redirs->heredoc_content);
		free(redirs);
		redirs = tmp;
	}
}

void	free_cmd_list(t_cmd *commands)
{
	t_cmd	*tmp;

	while (commands)
	{
		tmp = commands->next;
		if (commands->args)
			ft_freesplit(commands->args);
		if (commands->redirs)
			free_redirs(commands->redirs);
		free(commands);
		commands = tmp;
	}
}

void	cleanup_child(t_shell *shell, int status)
{
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmds)
		free_cmd_list(shell->cmds);
	if (shell->envp)
		free_environ(shell->envp);
	if (shell->last_path)
		free(shell->last_path);
	rl_clear_history();
	exit(status);
}
