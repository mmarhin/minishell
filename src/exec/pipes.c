/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:50:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/12/19 16:02:06 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_pipe_fds(t_pipe_ctx *ctx, int is_last)
{
	if (ctx->prev_fd != -1)
	{
		dup2(ctx->prev_fd, STDIN_FILENO);
		close(ctx->prev_fd);
	}
	if (!is_last)
	{
		close(ctx->pipefd[0]);
		dup2(ctx->pipefd[1], STDOUT_FILENO);
		close(ctx->pipefd[1]);
	}
}

static void	exec_pipe_child(t_cmd *cmd, t_shell *shell, t_pipe_ctx *ctx,
				int is_last)
{
	int	builtin_id;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipe_fds(ctx, is_last);
	if (cmd->redirs && apply_redirections(cmd->redirs) < 0)
		exit(1);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	builtin_id = is_builtin(cmd->args[0]);
	if (builtin_id)
	{
		exec_builtin(cmd->args, builtin_id, shell);
		exit(shell->exit_status);
	}
	exec_external(cmd->args, shell);
	perror(cmd->args[0]);
	exit(127);
}

static void	wait_all_pids(t_pipe_ctx *ctx, t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < ctx->count)
	{
		waitpid(ctx->pids[i], &status, 0);
		if (i == ctx->count - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

static int	fork_cmd(t_cmd *cmd, t_shell *shell, t_pipe_ctx *ctx)
{
	pid_t	pid;
	int		is_last;

	is_last = (cmd->next == NULL);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exec_pipe_child(cmd, shell, ctx, is_last);
	return (pid);
}

void	exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_pipe_ctx	ctx;
	t_cmd		*cmd;

	ctx.prev_fd = -1;
	ctx.count = 0;
	cmd = cmds;
	while (cmd)
	{
		if (cmd->next && pipe(ctx.pipefd) < 0)
			return (perror("pipe"));
		ctx.pids[ctx.count] = fork_cmd(cmd, shell, &ctx);
		if (ctx.pids[ctx.count] < 0)
			return ;
		if (ctx.prev_fd != -1)
			close(ctx.prev_fd);
		if (cmd->next)
		{
			close(ctx.pipefd[1]);
			ctx.prev_fd = ctx.pipefd[0];
		}
		cmd = cmd->next;
		ctx.count++;
	}
	wait_all_pids(&ctx, shell);
}
