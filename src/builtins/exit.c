/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:41 by lanton-m          #+#    #+#             */
/*   Updated: 2025/11/02 23:01:41 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_numeric(char *str)
{
	int i;

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

void	ft_exit(char **args, t_shell *shell)
{

	ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		free_environ(shell->envp);
		exit(shell->last_exit_code);
	}
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		shell->last_exit_code = 1;
		return;
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		free_environ(shell->envp);
		exit(2);
	}
	free_environ(shell->envp);
	exit(ft_atoi(args[1]) % 256);
}