/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:53 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 15:34:08 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_shell *shell)
{
	int		i;
	char	*frase;

	i = 0;
	frase = "declare -x";
	if (!shell->envp)
	{
		shell->exit_status = 0;
		return ;
	}
	while (shell->envp[i])
	{
		ft_putstr_fd(frase, 1);
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(shell->envp[i++], 1);
		ft_putchar_fd('\n', 1);
	}
	shell->exit_status = 0;
}

static int	valid_arg(char *key)
{
	int	i;

	i = 1;
	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalpha(key[i]) && !ft_isdigit(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_var(t_shell *shell, char *var)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(var, '=');
	if (eq)
	{
		key = ft_substr(var, 0, eq - var);
		if (!key)
			return ;
		value = eq + 1;
		set_env(shell, key, value);
		free(key);
	}
	else
		set_env(shell, var, "");
}

static void	print_error(char *arg, int *err_cod)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*err_cod = 1;
}

void	ft_export(t_shell *shell, char **args)
{
	int		i;
	int		err_cod;

	i = 1;
	err_cod = 0;
	if (!shell)
		return ;
	if (!args[1])
		print_env(shell);
	else
	{
		while (args[i])
		{
			if (valid_arg(args[i]))
				export_var(shell, args[i]);
			else
				print_error(args[i], &err_cod);
			i++;
		}
	}
	shell->exit_status = err_cod;
}
