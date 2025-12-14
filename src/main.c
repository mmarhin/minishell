/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:42:53 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/14 12:25:44 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(t_cmd *current, t_shell *shell)
{
	int	builtin_id;

	if (!current->args || !current->args[0])
		return ;
	builtin_id = is_builtin(current->args[0]);
	if (builtin_id)
		exec_builtin(current->args, builtin_id, shell);
	else
		exec_command(current, 0, shell);
}

static void	process_input(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*commands;
	t_cmd	*current;

	tokens = tokenize(line);
	if (!tokens)
		return ;
	commands = parse(tokens, shell);
	if (!commands)
	{
		free_tokens(tokens);
		return ;
	}
	current = commands;
	while (current)
	{
		execute_command(current, shell);
		current = current->next;
	}
	free_tokens(tokens);
	free_cmd_list(commands);
}

static int	init_shell(t_shell *shell, char **envp)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	shell->envp = copy_environ(envp);
	if (!shell->envp)
	{
		ft_putendl_fd("Error: failed to copy environment", 2);
		return (1);
	}
	shell->exit_status = 0;
	setup_signals_interactive();
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			process_input(line, shell);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell, envp))
		return (1);
	shell_loop(&shell);
	free_environ(shell.envp);
	ft_putendl_fd("exit", 1);
	return (shell.exit_status);
}
