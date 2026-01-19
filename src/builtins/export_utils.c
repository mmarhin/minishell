/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:00:00 by lanton-m          #+#    #+#             */
/*   Updated: 2026/01/19 11:23:56 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_line(char *env_line)
{
	int	j;

	j = 0;
	ft_putstr_fd("declare -x ", 1);
	while (env_line[j])
	{
		if (j > 0 && env_line[j - 1] == '=')
			ft_putstr_fd("\"", 1);
		ft_putchar_fd(env_line[j], 1);
		j++;
	}
	ft_putstr_fd("\"", 1);
	ft_putchar_fd('\n', 1);
}

void	print_export_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->envp)
	{
		shell->exit_status = 0;
		return ;
	}
	while (shell->envp[i])
	{
		print_env_line(shell->envp[i]);
		i++;
	}
	shell->exit_status = 0;
}

int	valid_export_arg(char *key)
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

void	export_concat(t_shell *shell, char *var)
{
	char	*plus_pos;
	char	*key;
	char	*old_value;
	char	*new_value;

	plus_pos = ft_strchr(var, '+');
	key = ft_substr(var, 0, plus_pos - var);
	if (!key)
		return ;
	old_value = get_env(shell, key);
	if (old_value)
		new_value = ft_strjoin(old_value, plus_pos + 2);
	else
		new_value = ft_strdup(plus_pos + 2);
	if (new_value)
	{
		set_env(shell, key, new_value);
		free(new_value);
	}
	free(key);
}

void	export_var(t_shell *shell, char *var, int code)
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
