/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:35:46 by lanton-m          #+#    #+#             */
/*   Updated: 2025/10/24 00:35:46 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_executable(const char *path)
{
	return (access(path, X_OK) == 0);
}

static char	*join_path(const char *dir, const char *cmd)
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

static char	*resolve_in_path(char **dir, const char *cmd)
{
	int		i;
	char	*full;

	i = 0;
	while (dir[i])
	{
		full = join_path(dir[i], cmd);
		if (full && is_executable(full))
			return (ft_freesplit(dir), full);
		free(full);
		i++;
	}
	return (ft_freesplit(dir), NULL);
}

char	*find_in_path(const char *cmd)
{
	const char	*path;
	char		**dir;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (is_executable(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = getenv("PATH");
	if (!path || !*path)
		return (NULL);
	dir = ft_split(path, ':');
	if (!dir)
		return (NULL);
	return (resolve_in_path(dir, cmd));
}

void	exec_external(char *const argv[], t_shell *shell)
{
	char	*path;

	path = find_in_path(argv[0]);
	if (!path)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(path, argv, shell->envp);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free(path);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}
