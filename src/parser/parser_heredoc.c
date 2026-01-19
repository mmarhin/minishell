/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarin- <mamarin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:00:00 by mamarin-          #+#    #+#             */
/*   Updated: 2026/01/19 11:27:43 by mamarin-         ###   ########.fr       */
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
	size_t	len;

	len = ft_strlen(line);
	if (!shell->interactive && len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
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
		line = process_heredoc_line(line, shell, qt);
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		content = append_heredoc_line(content, line);
		if (!content)
			return (NULL);
	}
	return (content);
}

int	check_pipe_start(t_token *tokens, t_shell *shell)
{
	if (!tokens || tokens->type == TOKEN_PIPE)
	{
		if (tokens && tokens->type == TOKEN_PIPE)
		{
			ft_putendl_fd("minishell: syntax error near `|'", 2);
			shell->exit_status = 2;
		}
		return (1);
	}
	return (0);
}
