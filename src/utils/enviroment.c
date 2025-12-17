/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:47:10 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/14 12:26:38 by mamarin-         ###   ########.fr       */
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
