/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:33 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/15 12:37:37 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell)
		return ;
	if (!shell->envp)
	{
		shell->exit_status = 0;
		return ;
	}
	while (shell->envp[i])
	{
		ft_putstr_fd(shell->envp[i++], 1);
		ft_putchar_fd('\n', 1);
	}
	shell->exit_status = 0;
}
