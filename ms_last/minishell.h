/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuramot <kkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:22:50 by kkuramot          #+#    #+#             */
/*   Updated: 2025/07/29 14:13:35 by kkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_shell
{
	char			**envp;
	int				last_status;
}					t_shell;

# define TOK_INIT_CAP 512
# define BUF_INIT_CAP 256

typedef struct s_cmd
{
	char			**args;
	int				infile;
	int				outfile;
	int				has_redir_error;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*value;
	char			quote;
}					t_token;

typedef struct s_parse_state
{
	size_t			i;
	t_token			*tok;
	size_t			j;
	size_t			cap;
}					t_parse_state;

void				execute_pipeline(char *line, t_shell *shell);
int					is_parent_builtin(char *cmd);
pid_t				execute_pipeline_loop(t_cmd *cmds, t_shell *shell,
						int prev_fd, pid_t last_pid);
int					execute_builtin(char **args, t_shell *shell);
void				execute_cmd(t_cmd *cmd, t_shell *shell);

void				execute_echo(char **args);
void				execute_cd(char **args, t_shell *shell);
char				*get_cd_target(char **args, char **envp, int *needs_free);
void				execute_pwd(void);
void				execute_export(char **args, t_shell *shell);
int					is_valid_identifier(const char *str);
void				print_identifier_error(const char *arg, int *last_status);
void				print_exported_vars(char **envp);
void				handle_export_assign(char *arg, t_shell *shell);
void				handle_export_append(char *arg, t_shell *shell);
void				execute_unset(char **args, t_shell *shell);
void				execute_env(char **args, t_shell *shell);
void				execute_exit(char **args);

int					is_unclosed_quote(const char *line);
t_cmd				*parse_commands(char *line, t_shell *shell);
void				handle_word_token(t_token *token, t_cmd *curr,
						t_shell *shell);
int					handle_redir_token(t_token **tokens_ptr, t_cmd *curr,
						t_shell *shell);
t_cmd				*create_and_link_cmd(t_cmd **head);

t_token				read_token(char **s);
void				skip_whitespace(char **s);
char				*strip_quotes(const char *str, char *quote_type);
char				*expand_variables(const char *str, t_shell *shell);
void				handle_quotes(char c, char *quote_state, char **result);
void				append_char_to_result(char **result, char c);
void				append_str_to_result(char **result, const char *s);
char				*expand_variables_no_quotes(const char *str,
						t_shell *shell);
char				**expand_variables_and_split(const char *str,
						t_shell *shell, int preserve_quotes);

int					setup_heredoc(char *limiter, t_shell *shell);
void				parse_redirection(char **s, t_cmd *cmd, t_shell *shell);
void				assign_fd_to_cmd(int fd, const char *op, t_cmd *cmd);

char				**copy_envp(char **envp);
void				free_envp(char **envp);
char				*get_env_value(const char *name, char **envp);
char				**overwrite_env(const char *key, const char *value,
						char **envp);
char				*create_env_entry(const char *key, const char *value);
void				free_cmd_list(t_cmd *head);

int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				**ft_split(char const *s, char c);
void				ft_free_split(char **arr);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
char				*ft_strcpy(char *dst, char *src);
char				*ft_strcat(char *dst, char *src);
char				*ft_strndup(const char *s, size_t n);
long long			ft_atoll(char *c);
void				*ft_calloc(size_t num, size_t size);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char				*ft_strjoin(char const *str, char const *s2);
void				*ft_memset(void *dest, int c, size_t count);
char				*ft_strstr(char *str, char *to_find);
char				*ft_itoa(int n);
void				ft_bzero(void *s, size_t n);
int					ft_isdigit(int c);
char				*ft_strrchr(const char *s, int c);
void				ft_putstr_fd(char *s, int fd);

char				*find_path(char *cmd, char **envp);
int					is_builtin(char *cmd);
void				free_tokens(t_token *tokens);
t_token				*shell_split_with_quotes(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
void				parse_redirection_token(t_token *op_token,
						t_token *file_token, t_cmd *cmd, t_shell *shell);
t_token				*shell_split(const char *s);
void				*ft_memcpy(void *dest, const void *src, size_t count);
char				**split_args_with_expansion(const char *line,
						t_shell *shell);
int					is_empty_or_whitespace(const char *str);
int					has_whitespace(const char *str);
int					is_quote(char c);
void				put_error_str(const char *s1, const char *s2,
						const char *s3);
int					is_all_redirection_chars(const char *s);
const char			*two_char_op(const char *s);
int					is_redirection(const char *s);
int					is_operator(const char *s);
int					is_op_char(char c);
int					is_fd_redirection(const char *s);
int					is_space(char c);
int					contains_unquoted_dollar(const char *s);
int					contains_operator_char(const char *s);
int					validate_syntax_tokens(t_token *tokens, t_shell *shell);
void				initialize_shell(t_shell *shell, char **envp);
char				*join_lines_for_quotes(char *line, char *newline);
int					is_quoted_whitespace(const char *str);
char				*expand_tilde_in_line(char *line, t_shell *shell);

void				setup_signals(t_shell *shell);
void				sigint_handler(int sig);
void				handle_sigint_interactive(int sig);
void				setup_signals_interactive(t_shell *shell);
void				setup_signals_non_interactive(void);

#endif