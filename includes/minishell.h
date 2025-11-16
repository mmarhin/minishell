/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:49:33 by lanton-m          #+#    #+#             */
/*   Updated: 2025/11/16 00:01:46 by lanton-m         ###   ########.fr       */
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

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**envp;
	int		last_exit_code;
}	t_shell;

extern volatile sig_atomic_t	g_sig;

/* executor_path.c */
char	*find_in_path(const char *cmd);
void	exec_external(char *const argv[], t_shell *shell);

/* executor.c */
void	exec_command(char **args, int background, t_shell *shell);

/* signals.c */
void	setup_signals_interactive(void);
void	handle_sigint(int sig);

/* cleaners.c */
void	ft_freesplit(char **split);
void	free_environ(char **envp);

/* enviroment.c*/
char	**copy_environ(char **envp);
char	*get_env(t_shell *shell, const char *key);
void	set_env(t_shell *shell, const char *key, const char *value);
void	unset_env(t_shell *shell, const char *key);

/* builtins.c */
int		is_builtin(const char *cmd);
void	exec_builtin(char **args, int builtin, t_shell *shell);

/* builtins */
void	ft_cd(char **args, t_shell *shell);
/*
void	ft_echo(char **args);
void	ft_pwd(void);
void	ft_env(t_shell *shell);
void	ft_export(char **args, t_shell *shell);
void	ft_unset(char **args, t_shell *shell);
*/
void	ft_exit(char **args, t_shell *shell);

#endif
