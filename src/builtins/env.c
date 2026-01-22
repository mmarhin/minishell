/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:33 by lanton-m          #+#    #+#             */
/*   Updated: 2026/01/19 13:13:49 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **args, t_shell *shell)
{
	int	i;

	if (args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		shell->exit_status = 127;
		return ;
	}
	i = 0;
	if (!shell || !shell->envp)
		return ;
	while (shell->envp[i])
	{
		ft_putstr_fd(shell->envp[i++], 1);
		ft_putchar_fd('\n', 1);
	}
	shell->exit_status = 0;
}
