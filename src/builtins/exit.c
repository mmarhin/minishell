/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:41 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 15:32:15 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_sign(char *str, int *i, int *sign)
{
	*i = 0;
	*sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (!str[*i])
		return (0);
	return (1);
}

static int	check_overflow(char *str, long *result)
{
	int		i;
	int		sign;
	long	num;

	if (!check_sign(str, &i, &sign))
		return (0);
	num = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (sign == 1 && (num > (LONG_MAX - (str[i] - '0')) / 10))
			return (0);
		if (sign == -1 && num > (LONG_MAX - (str[i] - '0')) / 10)
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	*result = num * sign;
	return (1);
}

static void	exit_numeric_error(char *arg, t_shell *shell)
{
	if (shell->interactive)
		ft_putendl_fd("exit", 1);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_environ(shell->envp);
	exit(2);
}

void	ft_exit(char **args, t_shell *shell)
{
	long	exit_code;

	if (shell->interactive)
		ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		free_environ(shell->envp);
		exit(shell->exit_status);
	}
	if (!check_overflow(args[1], &exit_code))
		exit_numeric_error(args[1], shell);
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	free_environ(shell->envp);
	exit((unsigned char)exit_code);
}
