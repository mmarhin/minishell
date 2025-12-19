/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:30:00 by mamarin-          #+#    #+#             */
/*   Updated: 2025/12/19 16:27:00 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (perror("dup2"), close(pipefd[0]), -1);
	close(pipefd[0]);
	return (0);
}
