/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:42:53 by lanton-m          #+#    #+#             */
/*   Updated: 2025/11/16 22:15:17 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*commands;
	t_cmd	*current;
	int		builtin_id;
	
	tokens = tokenize(line);
	if (!tokens)
		return ;
	commands = parse(tokens, shell);
	if (!commands)
	{
		free_tokens(tokens);
		return ;
	}
	// Ejecutar cada comando (temporal, sin pipes)
	current = commands;
	while (current)
	{
		if (current->args && current->args[0])
		{
			builtin_id = is_builtin(current->args[0])
			if (builtin_id)
				exec_builtin(current->args, builtin_id, shell);
			else
				exec_command(current->args, 0, shell);
		}
		current = current->next;
	}
	free_tokens(tokens);
	free_cmd_list(commands);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	(void)argc;
	(void)argv;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	shell.envp = copy_environ(envp);
	if (!shell.envp)
		return (ft_putendl_fd("Error: failed to copy environment", 2), 1);
	shell.exit_status = 0;
	setup_signals_interactive();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)  // Ctrl+D
			break ;
		if (*line)
		{
			add_history(line);
			process_input(line, &shell);
		}
		free(line);
	}
	free_environ(shell.envp);
	ft_putendl_fd("exit", 1);
	return (shell.exit_status);
}