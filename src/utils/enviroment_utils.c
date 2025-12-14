/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:00:00 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/14 12:27:01 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_existing_env(t_shell *shell, char *key_eq, const char *val)
{
	int		i;
	char	*new_entry;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], key_eq, ft_strlen(key_eq)))
		{
			new_entry = ft_strjoin(key_eq, val);
			if (!new_entry)
				return (-1);
			free(shell->envp[i]);
			shell->envp[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_new_env(t_shell *shell, char *key_eq, const char *value)
{
	int		i;
	char	**new_envp;
	char	*new_entry;

	i = 0;
	while (shell->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (-1);
	i = -1;
	while (shell->envp[++i])
		new_envp[i] = shell->envp[i];
	new_entry = ft_strjoin(key_eq, value);
	if (!new_entry)
		return (free(new_envp), -1);
	new_envp[i] = new_entry;
	new_envp[i + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);
}

void	set_env(t_shell *shell, const char *key, const char *value)
{
	char	*key_eq;
	int		ret;

	if (!shell || !shell->envp || !key || !value)
		return ;
	key_eq = ft_strjoin(key, "=");
	if (!key_eq)
		return ;
	ret = update_existing_env(shell, key_eq, value);
	if (ret == 0)
		add_new_env(shell, key_eq, value);
	free(key_eq);
}

static void	copy_unset_env(t_shell *shell, char **new_envp, char *key_eq)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], key_eq, ft_strlen(key_eq)))
			new_envp[j++] = shell->envp[i];
		else
			free(shell->envp[i]);
	}
	new_envp[j] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
}

void	unset_env(t_shell *shell, const char *key)
{
	int		i;
	char	*key_eq;
	char	**new_envp;

	if (!shell || !shell->envp || !key)
		return ;
	key_eq = ft_strjoin(key, "=");
	if (!key_eq)
		return ;
	i = 0;
	while (shell->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		return (free(key_eq));
	copy_unset_env(shell, new_envp, key_eq);
	free(key_eq);
}
