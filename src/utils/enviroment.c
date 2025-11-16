/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:47:10 by lanton-m          #+#    #+#             */
/*   Updated: 2025/11/02 23:47:10 by lanton-m         ###   ########.fr       */
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

void	set_env(t_shell *shell, const char *key, const char *value)
{
	int		i;
	int		j;
	char	*key_eq;
	char	*new_entry;
	char	**new_envp;

	i = 0;
	if (!shell || !shell->envp || !key || !value)
		return ;
	key_eq = ft_strjoin(key, "=");
	if (!key_eq)
		return ;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], key_eq, ft_strlen(key_eq)))
		{
			new_entry = ft_strjoin(key_eq, value);
			if (!new_entry)
			{
				free(key_eq);
				return ;
			}
			free(shell->envp[i]);
			shell->envp[i] = new_entry;
			free(key_eq);
			return ;				
		}
		i++;
	}
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
	{
		free (key_eq);
		return ;
	}
	j = 0;
	while ( j < i)
	{
		new_envp[j] = shell->envp[j];
		j++;
	}
	new_entry = ft_strjoin(key_eq, value);
	if (!new_entry)
	{
		free(new_envp);
		free(key_eq);
		return ;
	}
	new_envp[i] = new_entry;
	new_envp[i + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	free(key_eq);
}

void	unset_env(t_shell *shell, const char *key)
{
	int		i;
	int		j;
	int		k;
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
	{
		free(key_eq);
		return ;
	}
	j = 0;
	k = 0;
	while (j < i)
	{
		if (ft_strncmp(shell->envp[j], key_eq, ft_strlen(key_eq)))
			new_envp[k++] = shell->envp[j];
		else
			free(shell->envp[j]);
		j++;
	}
	new_envp[k] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	free(key_eq);
}