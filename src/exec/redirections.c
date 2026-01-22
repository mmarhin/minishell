/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:00:00 by lanton-m          #+#    #+#             */
/*   Updated: 2026/01/19 11:23:56 by mamarin-         ###   ########.fr       */
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

static int	apply_single_redir(t_redir *redir)
{
	if (redir->type == TOKEN_REDIR_IN)
		return (apply_redir_in(redir->file));
	else if (redir->type == TOKEN_REDIR_OUT)
		return (apply_redir_out(redir->file, 0));
	else if (redir->type == TOKEN_REDIR_APPEND)
		return (apply_redir_out(redir->file, 1));
	else if (redir->type == TOKEN_HEREDOC)
		return (apply_heredoc(redir->heredoc_content));
	return (0);
}

int	apply_redirections(t_redir *redirs, t_shell *shell)
{
	while (redirs)
	{
		if (apply_single_redir(redirs) < 0)
		{
			shell->exit_status = 1;
			return (-1);
		}
		redirs = redirs->next;
	}
	return (0);
}
