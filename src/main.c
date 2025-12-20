/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:42:53 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 19:58:59 by mamarin-         ###   ########.fr       */
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
	shell->interactive = isatty(STDIN_FILENO);
	setup_signals_interactive();
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;
	size_t	len;

	while (1)
	{
		if (shell->interactive)
		{
			line = readline("minishell> ");
			if (line && *line)
				add_history(line);
		}
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!shell->interactive)
		{
			len = ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
		}
		if (*line)
			process_input(line, shell);
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
	if (shell.interactive)
		ft_putendl_fd("exit", 1);
	return (shell.exit_status);
}
