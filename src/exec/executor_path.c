/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:35:46 by lanton-m          #+#    #+#             */
/*   Updated: 2026/01/19 11:23:56 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_executable(const char *path);
char	*join_path(const char *dir, const char *cmd);

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

static char	*try_current_dir(const char *cmd)
{
	char	*full;

	full = join_path(".", cmd);
	if (full && is_executable(full))
		return (full);
	free(full);
	return (NULL);
}

char	*find_in_path(const char *cmd, t_shell *shell)
{
	char	*path;
	char	**dir;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (is_executable(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = get_env(shell, "PATH");
	if (!path || !*path)
		return (try_current_dir(cmd));
	dir = ft_split(path, ':');
	if (!dir)
		return (NULL);
	return (resolve_in_path(dir, cmd));
}

void	exec_external(char *const argv[], t_shell *shell)
{
	char	*path;

	path = find_in_path(argv[0], shell);
	if (!path)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		cleanup_child(shell, 127);
	}
	execve(path, argv, shell->envp);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free(path);
	if (errno == ENOENT)
		cleanup_child(shell, 127);
	cleanup_child(shell, 126);
}
