/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:06 by lanton-m          #+#    #+#             */
/*   Updated: 2025/11/02 23:01:06 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **args, t_shell *shell)
{
	char	*home;

	if (!args[1])
	{
		home = get_env(shell, "HOME");
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return ;
		}
		if (chdir(home) == -1)
			perror("cd");
	}
	else
	{
		if (args[2])
		{
			ft_putendl_fd("cd: too many arguments", 2);
			return ;
		}
		if (chdir(args[1]) == -1)
			perror("cd");
	}
}