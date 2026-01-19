/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/01/19 12:48:01 by mamarin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_line(t_shell *shell)
{
	if (shell->interactive)
		return (readline("> "));
	return (get_next_line(STDIN_FILENO));
}

static char	*process_heredoc_line(char *line, t_shell *shell, t_quote_type qt)
{
	char	*tmp;

	if (qt == NO_QUOTE)
	{
		tmp = expand_string(line, shell, DOUBLE_QUOTE);
		free(line);
		return (tmp);
	}
	return (line);
}

static char	*append_heredoc_line(char *content, char *line)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(content, line);
	free(content);
	free(line);
	result = ft_strjoin(tmp, "\n");
	free(tmp);
	return (result);
}

char	*read_heredoc_content(char *delim, t_shell *shell, t_quote_type qt)
{
	char	*content;
	char	*line;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (1)
	{
		line = get_heredoc_line(shell);
		if (!line)
			break ;
		if (!shell->interactive && ft_strlen(line) > 0
			&& line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		line = process_heredoc_line(line, shell, qt);
		content = append_heredoc_line(content, line);
		if (!content)
			return (NULL);
	}
	return (content);
}

int	fill_heredoc(t_redir *redir, t_token *tk, t_shell *shell)
{
	redir->file = ft_strdup(tk->value);
	if (!redir->file)
		return (-1);
	redir->heredoc_content = read_heredoc_content(redir->file, shell,
			tk->quote);
	if (!redir->heredoc_content)
		return (free(redir->file), -1);
	return (0);
}
