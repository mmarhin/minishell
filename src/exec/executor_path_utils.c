/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:00:00 by lanton-m          #+#    #+#             */
/*   Updated: 2026/01/19 11:23:56 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_executable(const char *path)
{
	return (access(path, X_OK) == 0);
}

char	*join_path(const char *dir, const char *cmd)
{
	size_t	ld;
	size_t	lc;
	char	*out;

	ld = ft_strlen(dir);
	lc = ft_strlen(cmd);
	out = (char *)malloc(ld + 1 + lc + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, dir, ld);
	out[ld] = '/';
	ft_memcpy(out + ld + 1, cmd, lc + 1);
	return (out);
}
