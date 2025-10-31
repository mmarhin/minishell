/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shell_project.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:58:35 by lanton-m          #+#    #+#             */
/*   Updated: 2025/10/27 10:58:35 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
	{
		if (!args[1])
			chdir("/");
		else if (chdir(args[1]) != 0)
			perror("cd");
	}
	else if (ft_strcmp(args[0], "exit") == 0)
		exit(0);
}

static void	exec_command(char **args, int background)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		exec_external(args);
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	if (background == 0)
		waitpid(pid, &status, WUNTRACED);
	else
	{
		printf("Background job running... pid: %d, command: %s\n",
			pid, args[0]);
	}
}

static void	process_input(char *line)
{
	char	**args;

	if (!line)
	{
		write(1, "exit\n", 5);
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
	if (ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "exit") == 0)
		exec_builtin(args);
	else
		exec_command(args, 0);
	ft_freesplit(args);
}

int	main(void)
{
	char	*line;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		setup_signals_interactive();
		line = readline("minishell> ");
		process_input(line);
		free(line);
	}
	return (0);
}
