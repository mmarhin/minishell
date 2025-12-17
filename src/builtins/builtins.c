/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 22:47:10 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/15 20:30:07 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (2);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (3);
	else if (ft_strcmp(cmd, "env") == 0)
		return (4);
	else if (ft_strcmp(cmd, "export") == 0)
		return (5);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (6);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (7);
	return (0);
}

void	exec_builtin(char **args, int builtin, t_shell *shell)
{
	if (builtin == 1)
		ft_cd(args, shell);
	if (builtin == 2)
		ft_echo(args, shell);
	if (builtin == 3)
		ft_pwd(shell);
	if (builtin == 4)
		ft_env(shell);
	if (builtin == 5)
		ft_export(shell, args);
	if (builtin == 6)
		ft_unset(shell, args);
	else if (builtin == 7)
		ft_exit(args, shell);
}
