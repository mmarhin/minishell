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
	char	buffer[PATH_MAX];

	home = get_env(shell, "HOME");
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		shell->exit_status = 1;
		return ;
	}
	if (shell->last_path)
		free(shell->last_path);
	shell->last_path = ft_strdup(getcwd(buffer, PATH_MAX));
	if (chdir(home) == -1)
	{
		perror("cd");
		shell->exit_status = 1;
		return ;
	}
	shell->exit_status = 0;
}

static void	cd_previous(t_shell *shell)
{
	char	buffer[PATH_MAX];
	char	*current;

	if (!shell->last_path)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		shell->exit_status = 1;
		return ;
	}
	current = ft_strdup(getcwd(buffer, PATH_MAX));
	if (chdir(shell->last_path) == -1)
	{
		perror("cd");
		free(current);
		shell->exit_status = 1;
		return ;
	}
	ft_putendl_fd(shell->last_path, 1);
	free(shell->last_path);
	shell->last_path = current;
	shell->exit_status = 0;
}

void	ft_cd(char **args, t_shell *shell)
{
	char	buffer[PATH_MAX];
	char	*old_path;

	if (!args[1] || args[1][0] == '~')
		return (cd_home(shell));
	if (args[1][0] == '-' && args[1][1] == '\0' && !args[2])
		return(cd_previous(shell));
	if (args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	old_path = ft_strdup(getcwd(buffer, PATH_MAX));
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		shell->exit_status = 1;
		return ;
	}
	if (shell->last_path)
		free(shell->last_path);
	shell->last_path = old_path;
	shell->exit_status = 0;
}
