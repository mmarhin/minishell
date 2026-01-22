/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:53 by lanton-m          #+#    #+#             */
/*   Updated: 2026/01/19 11:23:56 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_export_env(t_shell *shell);
void			export_var(t_shell *shell, char *var, int code);
static int		valid_export_arg(char *key);

static int	valid_export_arg(char *key)
{
	int	i;

	i = 1;
	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (key[i] == '+' && key[i + 1] == '=')
			return (2);
		if (!ft_isalpha(key[i]) && !ft_isdigit(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	handle_invalid_opt(t_shell *shell, char *arg, int *err_cod)
{
	ft_putstr_fd("export: -", 2);
	ft_putchar_fd(arg[1], 2);
	ft_putendl_fd(": invalid option", 2);
	shell->exit_status = 2;
	*err_cod = 2;
}

static void	handle_invalid_id(char *arg, int *err_cod)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*err_cod = 1;
}

static int	process_export_args(t_shell *shell, char **args)
{
	int	i;
	int	err_cod;
	int	arg_ret;

	i = 0;
	err_cod = 0;
	while (args[++i])
	{
		if (args[i][0] == '-')
			handle_invalid_opt(shell, args[i], &err_cod);
		else
		{
			arg_ret = valid_export_arg(args[i]);
			if (arg_ret)
				export_var(shell, args[i], arg_ret);
			else
				handle_invalid_id(args[i], &err_cod);
		}
	}
	return (err_cod);
}

void	ft_export(t_shell *shell, char **args)
{
	if (!shell)
		return ;
	if (!args[1])
	{
		print_export_env(shell);
		shell->exit_status = 0;
	}
	else
		shell->exit_status = process_export_args(shell, args);
}
