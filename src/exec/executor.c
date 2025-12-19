/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:45:22 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 16:45:49 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}

static void	exec_child(t_cmd *cmd, t_shell *shell)
{
	setup_child_signals();
	if (cmd->redirs && apply_redirections(cmd->redirs) < 0)
		exit(1);
	exec_external(cmd->args, shell);
	perror(cmd->args[0]);
	exit(EXIT_FAILURE);
}

static void	wait_child(pid_t pid, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
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

void	execute_single_cmd(t_cmd *current, t_shell *shell)
{
	int	builtin_id;
	int	saved[2];

	if (!current->args || !current->args[0])
		return ;
	builtin_id = is_builtin(current->args[0]);
	if (!builtin_id)
		return (exec_command(current, 0, shell));
	saved[0] = dup(STDIN_FILENO);
	saved[1] = dup(STDOUT_FILENO);
	if (current->redirs && apply_redirections(current->redirs) < 0)
	{
		dup2(saved[0], STDIN_FILENO);
		dup2(saved[1], STDOUT_FILENO);
		close(saved[0]);
		close(saved[1]);
		shell->exit_status = 1;
		return ;
	}
	exec_builtin(current->args, builtin_id, shell);
	dup2(saved[0], STDIN_FILENO);
	dup2(saved[1], STDOUT_FILENO);
	close(saved[0]);
	close(saved[1]);
}
