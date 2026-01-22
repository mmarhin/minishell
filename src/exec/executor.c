/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:45:22 by lanton-m          #+#    #+#             */
/*   Updated: 2026/01/19 11:27:43 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_signals(void);
void	wait_child(pid_t pid, t_shell *shell);
void	restore_fds(int *saved);

static void	exec_child(t_cmd *cmd, t_shell *shell)
{
	setup_child_signals();
	if (cmd->redirs && apply_redirections(cmd->redirs, shell) < 0)
		exit(1);
	exec_external(cmd->args, shell);
	perror(cmd->args[0]);
	exit(EXIT_FAILURE);
}

void	exec_command(t_cmd *cmd, int background, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
		exec_child(cmd, shell);
	if (background == 0)
		wait_child(pid, shell);
}

static int	handle_empty_cmd(t_cmd *current, t_shell *shell)
{
	if (!current->args || !current->args[0])
	{
		if (current->redirs && apply_redirections(current->redirs, shell) < 0)
			shell->exit_status = 1;
		return (1);
	}
	return (0);
}

void	execute_single_cmd(t_cmd *current, t_shell *shell)
{
	int	builtin_id;
	int	saved[2];

	if (handle_empty_cmd(current, shell))
		return ;
	builtin_id = is_builtin(current->args[0]);
	if (!builtin_id)
		return (exec_command(current, 0, shell));
	saved[0] = dup(STDIN_FILENO);
	saved[1] = dup(STDOUT_FILENO);
	if (current->redirs && apply_redirections(current->redirs, shell) < 0)
	{
		restore_fds(saved);
		shell->exit_status = 1;
		return ;
	}
	exec_builtin(current->args, builtin_id, shell);
	restore_fds(saved);
}
