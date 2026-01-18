/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:01:53 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/20 13:56:29 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_shell *shell)
{
	int		i;
	int		j;
	char	*frase;

	i = 0;
	j = 0;
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
		while (shell->envp[i][j])
		{
			if (j > 0 && shell->envp[i][j - 1] == '=')
				ft_putstr_fd("\"", 1);
			ft_putchar_fd(shell->envp[i][j], 1);
			j++;
		}
		i++;
		j = 0;
		ft_putstr_fd("\"", 1);
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
		if (key[i] == '+' && key[i + 1] == '=')
			return (2);
		if (!ft_isalpha(key[i]) && !ft_isdigit(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_concat(t_shell *shell, char *var)
{
	char	*plus_pos;
	char	*key;
	char	*value;
	char	*old_value;
	char	*new_value;

	plus_pos = ft_strchr(var, '+');
	key = ft_substr(var, 0, plus_pos - var);
	if (!key)
		return ;
	value = plus_pos + 2;
	old_value = get_env(shell, key);
	if (old_value)
		new_value = ft_strjoin(old_value, value);
	else
		new_value = ft_strdup(value);
	if (new_value)
	{
		set_env(shell, key, new_value);
		free(new_value);
	}
	free(key);
}

static void	export_var(t_shell *shell, char *var, int code)
{
	char	*eq;
	char	*key;
	char	*value;

	if (code == 2)
		return (export_concat(shell, var));
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
		{
			ft_putstr_fd("export: -", 2);
			ft_putchar_fd(args[i][1], 2);
			ft_putendl_fd(": invalid option", 2);
			shell->exit_status = 2;
			err_cod = 2;
		}
		else
		{
		arg_ret = valid_arg(args[i]);
		if (arg_ret)
			export_var(shell, args[i], arg_ret);
		else
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			err_cod = 1;
		}
		}
	}
	return (err_cod);
}

void	ft_export(t_shell *shell, char **args)
{
	if (!shell)
		return ;
	if (!args[1])
		print_env(shell);
	else
		shell->exit_status = process_export_args(shell, args);
	if (!args[1])
		shell->exit_status = 0;
}
