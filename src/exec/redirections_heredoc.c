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

int	apply_heredoc(char *content)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		return (perror("pipe"), -1);
	if (content)
		write(pipefd[1], content, ft_strlen(content));
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (perror("dup2"), close(pipefd[0]), -1);
	close(pipefd[0]);
	return (0);
}
