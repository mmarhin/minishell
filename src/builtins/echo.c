/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:30 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 09:35:06 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n(char *str)
{
	int	i;

	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_echo(char **args, t_shell *shell)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		if (check_n(args[i]))
			new_line = 0;
		else
			break ;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	shell->exit_status = 0;
}
