/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:00:00 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/19 16:37:34 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	return (-1);
}

static int	apply_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (redir_error(file));
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror("dup2"), close(fd), -1);
	close(fd);
	return (0);
}

static int	apply_redir_out(char *file, int append)
{
	int	fd;
	int	flags;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
		return (redir_error(file));
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror("dup2"), close(fd), -1);
	close(fd);
	return (0);
}

int	apply_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_IN
			&& apply_redir_in(redirs->file) < 0)
			return (-1);
		else if (redirs->type == TOKEN_REDIR_OUT
			&& apply_redir_out(redirs->file, 0) < 0)
			return (-1);
		else if (redirs->type == TOKEN_REDIR_APPEND
			&& apply_redir_out(redirs->file, 1) < 0)
			return (-1);
		else if (redirs->type == TOKEN_HEREDOC
			&& apply_heredoc(redirs->file) < 0)
			return (-1);
		redirs = redirs->next;
	}
	return (0);
}
