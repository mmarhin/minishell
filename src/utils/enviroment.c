/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:47:10 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/20 12:38:57 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_environ(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (ft_freesplit(new_envp), NULL);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char	*get_env(t_shell *shell, const char *key)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!shell || !shell->envp || !key)
		return (NULL);
	while (shell->envp[i] != NULL)
	{
		while (key[j] == shell->envp[i][j])
		{
			j++;
			if (!key[j] && shell->envp[i][j] == '=')
				return (shell->envp[i] + j + 1);
		}
		j = 0;
		i++;
	}
	return (NULL);
}

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
