/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:41 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/14 12:24:50 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_numeric_error(char *arg, t_shell *shell)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_environ(shell->envp);
	exit(2);
}

void	ft_exit(char **args, t_shell *shell)
{
	ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		free_environ(shell->envp);
		exit(shell->exit_status);
	}
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	if (!is_numeric(args[1]))
		exit_numeric_error(args[1], shell);
	free_environ(shell->envp);
	exit(ft_atoi(args[1]) % 256);
}
