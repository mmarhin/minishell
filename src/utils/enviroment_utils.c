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

static void	copy_unset_env(t_shell *shell, char **new_envp, char *key_eq)
{
	int		i;
	int		j;
	size_t	key_len;

	i = -1;
	j = 0;
	key_len = ft_strlen(key_eq);
	while (shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], key_eq, key_len) != 0)
			new_envp[j++] = shell->envp[i];
		else
			free(shell->envp[i]);
	}
	new_envp[j] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
}

static int	env_exists(t_shell *shell, char *key_eq, size_t key_len)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], key_eq, key_len) == 0)
			return (1);
		i++;
	}
	return (0);
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
	if (!env_exists(shell, key_eq, ft_strlen(key_eq)))
		return (free(key_eq));
	i = 0;
	while (shell->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		return (free(key_eq));
	copy_unset_env(shell, new_envp, key_eq);
	free(key_eq);
}
