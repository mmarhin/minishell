/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:42:53 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 16:53:15 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*commands;

	tokens = tokenize(line);
	if (!tokens)
		return ;
	commands = parse(tokens, shell);
	if (!commands)
	{
		free_tokens(tokens);
		return ;
	}
	if (commands->next)
		exec_pipeline(commands, shell);
	else
		execute_single_cmd(commands, shell);
	free_tokens(tokens);
	free_cmd_list(commands);
}

static int	init_shell(t_shell *shell, char **envp)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	shell->envp = copy_environ(envp);
	if (!shell->envp)
		return (ft_putendl_fd("Error: failed to copy environment", 2), 1);
	shell->exit_status = 0;
	setup_signals_interactive();
	print_banner();
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = get_prompt(shell->exit_status);
		line = readline(prompt);
		free(prompt);
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
