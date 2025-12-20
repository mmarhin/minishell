/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:06 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 20:26:20 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home(t_shell *shell)
{
	char	*home;

	home = get_env(shell, "HOME");
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		shell->exit_status = 1;
		return ;
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		shell->exit_status = 1;
		return ;
	}
	shell->exit_status = 0;
}

void	ft_cd(char **args, t_shell *shell)
{
	if (!args[1] || args[1][0] == '~')
		return (cd_home(shell));
	if (args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		shell->exit_status = 1;
		return ;
	}
	shell->exit_status = 0;
}
