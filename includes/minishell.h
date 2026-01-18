/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:49:33 by lanton-m          #+#    #+#             */
/*   Updated: 2025/12/20 11:56:43 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_LINE 256

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}								t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	MIXED_QUOTE
}								t_quote_type;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	t_quote_type				quote;
	struct s_token				*next;
}								t_token;

typedef struct s_redir
{
	t_token_type				type;
	char						*file;
	char						*heredoc_content;
	struct s_redir				*next;
}								t_redir;

typedef struct s_cmd
{
	char						**args;
	t_redir						*redirs;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_shell
{
	char							**envp;
	int								exit_status;
	int								interactive;
	char							*last_path;
}								t_shell;

typedef struct s_parse_ctx
{
	t_cmd						*first;
	t_cmd						*last;
	t_shell						*shell;
}								t_parse_ctx;

typedef struct s_pipe_ctx
{
	int							pipefd[2];
	int							prev_fd;
	pid_t						pids[256];
	int							count;
}								t_pipe_ctx;

extern volatile sig_atomic_t	g_sig;

/* commands_expansion.c*/
char							*expand_string(char *str, t_shell *shell,
									t_quote_type quote);

/* executor_path.c */
char							*find_in_path(const char *cmd);
void							exec_external(char *const argv[],
									t_shell *shell);

/* executor.c */
void							exec_command(t_cmd *cmd, int background,
									t_shell *shell);
void							execute_single_cmd(t_cmd *current,
									t_shell *shell);

/* redirections.c */
int								apply_redirections(t_redir *redirs, t_shell *shell);

/* pipes.c */
void							exec_pipeline(t_cmd *cmds, t_shell *shell);

/* redirections_heredoc.c */
int								apply_heredoc(char *content);

/* signals.c */
void							setup_signals_interactive(void);
void							handle_sigint(int sig);

/* cleaners.c */
void							ft_freesplit(char **split);
void							free_environ(char **envp);
void							free_cmd_list(t_cmd *commands);

/* banner.c */
void							print_banner(void);
char							*get_prompt(int exit_status);

/* enviroment.c*/
char							**copy_environ(char **envp);
char							*get_env(t_shell *shell, const char *key);
void							set_env(t_shell *shell, const char *key,
									const char *value);
void							unset_env(t_shell *shell, const char *key);

/* builtins.c */
int								is_builtin(const char *cmd);
void							exec_builtin(char **args, int builtin,
									t_shell *shell);

/* builtins */
void							ft_cd(char **args, t_shell *shell);
void							ft_pwd(t_shell *shell);
void							ft_echo(char **args, t_shell *shell);
void							ft_env(t_shell *shell);
void							ft_export(t_shell *shell, char **args);
void							ft_unset(t_shell *shell, char **args);
void							ft_exit(char **args, t_shell *shell);

/* tokenizer/tokenizer.c */
t_token							*tokenize(char *input, t_shell *shell);

/* tokenizer/token_utils.c */
t_token							*create_token(t_token_type type, char *value,
									t_quote_type quote);
void							add_token(t_token **head, t_token *new_token);
void							free_tokens(t_token *head);

/* tokenizer/tokenizator_helpers.c */
int								is_space(char c);
int								is_operator(char c);
void							skip_spaces(char **str);
char							*extract_word(char **str);
int								is_quote(char c);
char							*extract_quoted_string(char **str,
									t_quote_type *quote_type);

/* tokenizer/tokenizator_operators.c */
t_token							*create_operator_token(char **str);
t_token							*handle_operator(char **input, t_token *head);
t_token							*handle_word(char **input, t_token *head,
									t_shell *shell);

/* parser/parser.c */
t_cmd							*parse(t_token *tokens, t_shell *shell);

/* parser/parser_utils.c */
t_cmd							*cmd_init(void);
t_redir							*redir_init(t_token_type type);
void							add_arg(t_shell *shell, t_cmd *aux,
									t_token *tks);
void							add_redir_to_cmd(t_cmd *cmd, t_redir *redir);
int								is_redir(t_token_type type);

#endif
