/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:49:33 by lanton-m          #+#    #+#             */
/*   Updated: 2025/10/30 12:59:28 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define MAX_LINE 256

extern volatile sig_atomic_t	g_sig;

/* executor_path.c */
char	*find_in_path(const char *cmd);
void	exec_external(char *const argv[]);

/* signals.c */
void	setup_signals_interactive(void);
void	handle_sigint(int sig);

/* cleaners.c */
void	ft_freesplit(char **split);

#endif
