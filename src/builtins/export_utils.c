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
	int	found_eq;

	j = 0;
	found_eq = 0;
	ft_putstr_fd("declare -x ", 1);
	while (env_line[j])
	{
		ft_putchar_fd(env_line[j], 1);
		if (!found_eq && env_line[j] == '=')
		{
			ft_putstr_fd("\"", 1);
			found_eq = 1;
		}
		j++;
	}
	if (found_eq)
		ft_putstr_fd("\"", 1);
	ft_putchar_fd('\n', 1);
}

static void	sort_env_array(char **arr, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export_env(t_shell *shell)
{
	int		i;
	int		count;
	char	**sorted;

	count = 0;
	if (!shell->envp)
		return ;
	while (shell->envp[count])
		count++;
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return ;
	i = -1;
	while (++i < count)
		sorted[i] = shell->envp[i];
	sorted[count] = NULL;
	sort_env_array(sorted, count);
	i = -1;
	while (sorted[++i])
		print_env_line(sorted[i]);
	free(sorted);
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
