/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:42:53 by lanton-m          #+#    #+#             */
/*   Updated: 2025/11/02 22:42:53 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(char *line, t_shell *shell)
{
	char	**args;
	int		builtin;

	if (!line)
	{
		write(1, "exit\n", 5);
		free_environ(shell->envp);
		exit(0);
	}
	if (*line)
		add_history(line);
	args = ft_split(line, ' ');
	if (!args || !args[0])
	{
		ft_freesplit(args);
		return ;
	}
	builtin = is_builtin(args[0]);
	if (builtin)
		exec_builtin(args, builtin, shell);
	else
		exec_command(args, 0, shell);
	ft_freesplit(args);
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
	shell.last_exit_code = 0;
	setup_signals_interactive();
	while (1)
	{
		line = readline("minishell> ");
		process_input(line, &shell);
		free(line);
	}
	free_environ(shell.envp);
	return (0);
}
