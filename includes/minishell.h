/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:57:04 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 11:59:42 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

# ifdef __linux__
#  define _GNU_SOURCE
#  include <features.h>
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <signal.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "enum.h"
# include "structures.h"
# include "debug.h"

# ifdef __APPLE__
#  include <limits.h>
# elif __linux__
#  include <linux/limits.h>
# endif

# define BUILTINS_STRING "echo,cd,env,exit,export,pwd,unset"
# define SPACES " \t\n"
# define BUILTIN_AMOUNT 7
# define BUFFER_SIZE 1
# define DEBUGG_PARSING 1
# define TEST_MODE 1

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define GREENBG "\033[42m"
# define REDBG "\033[41m"

// int	g_sig;

/* * * * * * * * * * * * * * * * INIT * * * * * * * * * * * * * * * * * * * */

int				init_mini(t_mini *mini, char **envp);
int				count_cmd(t_mini *mini);

void			signal_list(void);

/* * * * * * * * * * * * * * * PARSING * * * * * * * * * * * * * * * * * * * */

void			parsing(t_mini *mini, t_cmd *cmd);

int				count_arguments(t_mini *mini);
int				init_redirections(t_mini *mini, t_cmd *cmd);
int				init_arguments(t_mini *mini, t_cmd *cmd);

void			fill_cmd_structure(t_mini *mini, t_cmd *cmd);
char			*get_cmd_bin(t_mini *mini);
int				get_cmd_type(t_mini *mini, t_cmd *cmd);
int				get_cmd_redirection(t_mini *mini, t_cmd *cmd, int index);

int				is_builtin_echo(t_cmd *cmd);

int				count_arguments(t_mini *mini);
int				init_redirections(t_mini *mini, t_cmd *cmd);
int				init_arguments(t_mini *mini, t_cmd *cmd);

char			*dollar_handle(t_mini *mini, char *line);
char			*get_env_variable(t_mini *mini, char *line, int envp_i, int sub_i);
char			*empty_expand(t_mini *mini, char *temp1, t_quote q, int i);
int				get_envp_index(t_mini *mini, char *variable);
int				is_minishell_punct(char c);

void			expand_tildes(t_mini *mini);
void			init_quotes(t_quote *q);
int				is_valid_quote_basckslash(t_mini *mini);
void			quote_enclosure_handle(char c, t_quote *quote);
int				strlen_quote_cleaned_command(char *str);
char			*clean_command_quotes(t_mini *mini, char *str);
char			last_quote(char *str, int i);

char			*wildcard_handle(t_mini *mini, char *temp);
int				is_valid_filename(char *token, struct dirent *s_dir, int i, int j);
void			fill_file_list(t_mini *mini, t_wildcard *w);
int				count_valid_files(t_wildcard *w);
void			change_affixes(t_mini *mini, t_wildcard *w, int i);
char			*crop_command(t_mini *mini, char *line, t_wildcard *w);
int				get_new_index(char *temp);
int				get_dir_start(char *temp, int i);
void			set_wildcard_directory(t_mini *mini, t_wildcard *w, int i);
int				is_last_asterisk(char *token, int i);
void			tokenize_wildcard(t_mini *mini, t_wildcard *w, int start);
void			set_wildcard(t_mini *mini, char *temp, t_wildcard *w);
void			set_sub_token(t_mini *mini, t_wildcard *w);
void			init_wildcard_struct(t_wildcard *w);
void			free_wildcards(char *line, t_wildcard *w);


/* * * * * * * * * EXECUTION * * * * * * * * */

int				exec_mini(t_mini *mini, t_cmd *cmd);
void			handle_builtin(t_mini *mini, t_cmd *cmd);
t_builtin_func	get_builtin_function(t_cmd *cmd, char *cmd_name);
void			backup_standard_fd(t_mini *mini);
void			process_all_heredocs(t_mini *mini, t_cmd *cmd);
void			create_args_array(t_mini *mini, t_cmd *cmd);
void			dup2_fd(t_mini *mini, t_cmd *cmd, int fd_to_clone, int fd_new_clone);
void			set_and_execute_pipeline(t_mini *mini, t_cmd *cmd);
void			connect_command_pipeline(t_mini *mini, t_cmd *cmd, int cmd_index);
void			setup_redirections(t_mini *mini, t_cmd *cmd);
int				wait_for_children(t_mini *mini, t_cmd *cmd);
void			parent_closes_all_pipes(t_mini *mini);
void			restore_standard_fd(t_mini *mini);
//builtin exec
char			*ft_get_env(t_mini *mini, char *var_name);
int				set_env(t_mini *mini, char *env_key, char *env_row);
int				update_pwd_env(t_mini *mini, char *env_var);
int				update_old_pwd_env(t_mini *mini);
char			*get_current_workdir(t_mini *mini);
char			*get_new_env_row(t_mini *mini, char *env_key, char *new_path);
//utils exec (binaries)

/* * * * * * * * * * * * * * BUILTINS * * * * * * * * * * * * * * * */

int				builtin_cd(t_mini *mini, t_cmd *cmd);
int				builtin_echo(t_mini *mini, t_cmd *cmd);
int				builtin_env(t_mini *mini, t_cmd *cmd);
int				builtin_exit(t_mini *mini, t_cmd *cmd);
int				builtin_export(t_mini *mini, t_cmd *cmd);
int				builtin_pwd(t_mini *mini, t_cmd *cmd);
// int			builtin_unset(t_mini *mini, t_cmd *cmd);

/* * * * * * * * * * * * * * CHECKS * * * * * * * * * * * * * * * * * */

int				is_valid_pipes(t_mini *mini);
int				is_valid_redirections(t_mini *mini);
int				is_valid_backslash(t_mini *mini);
int				is_valid_syntax(char *command);
int				is_valid_arithmetic_exit(char *str);
int				is_directory(char *line);

/* * * * * * * * * * * * * * PRINT * * * * * * * * * * * * * * * * * */

void			print_unexpected_token(char *token);
void			print_char_table(char **string, char *name);
void			print_string(char *string, char *name);
void			print_cmd(t_cmd cmd, char *cmd_line);

void			print_quote_statement_debug(t_mini *mini, int i, t_quote *q);

/* * * * * * * * * * * * * * UTILS * * * * * * * * * * * * * * * * * */

				/* LIBFT */

int				ft_atoi(char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
char			*ft_itoa(int n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memset(void	*b, int c, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_sized_strdup(char *s, int size);
char			**ft_split(char *s, char c);
char			*ft_strchr(char *s, int c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strdup(char *s1);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
int				ft_strncmp(char *s1, char *s2, size_t n);
char			*ft_strnstr(char *haystack, char *needle, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_toupper(int c);
int				ft_tolower(int c);

				/* GNL */

char			*get_next_line(int fd);

				/* XTRA */

bool			contain_char(const char *s, char c);
int				get_int_len(int n);
void			append_space_to_string(t_mini *mini, t_wildcard *w, char **str);
char			*join_n_strings_wildcards(t_mini *mini, t_wildcard *w);
char			*join_three_strings(char *s1, char *s2, char *s3);
void			sort_array(char **filename, int len);
void			sort_ascii_array(char	**string_array, int len);
bool			contain_quotes(char *s);
char			*enquote_str(char *str, int q);
int				contain_string_at_specific_index(char *haystack, char *needle, int i);
bool			is_space(char c);
int				is_only_spaces(char *s);
int				is_only_specific_char(char *s, char c);
char			*epurstring(char *src);
int				is_quote(char c);
int				is_angle_bracket(char c);
int				start_with(char *string, char *start_string);
int				double_array_len(char **table);
int				ft_strcmp_alpha(char *s1, char *s2);
char			*get_line_from_stdin(void);

/* * * * * * * * * * STRING_ARRAY_FUNCTIONS * * * * * * * * * * * * */

char			**string_array_copy(t_mini *mini, t_cmd *cmd, char **src);
char			*string_array_find_string(char **string_array, char *string_to_find);
void			string_array_print(t_cmd *cmd, char **string_array);
size_t			string_array_len(char **str);
char			*string_array_create_key(char *variable, int variable_len);
char			**string_array_push(char **original_arr, char *new_ptr);
void			string_build(char **dest_ptr, char *prefix, char *suffix);
char			*string_array_join(char	**array);

/* * * * * * * * * * PRINT_ERRORS * * * * * * * * * * * * */

void			print_error(const char *format, const char *path, int fd);

/* * * * * * * * * * * FREEING FUNCTIONS * * * * * * * * * * * * * * */

void			free_string_array(char ***str);
void			free_wildcard_struct(t_wildcard *w);
void			free_cmd(t_mini *mini, t_cmd *cmd);
void			free_mini(t_mini *mini);
void			free_pathnames(t_cmd *cmd);
// void			free_wildcard_struct(t_wildcard *w);
void			exit_minishell(t_mini *mini, t_cmd *cmd);
void			free_string_ptr(char **str);
void			str_malloc_check(t_mini *mini, char *str);
void			dbl_str_malloc_check(t_mini *mini, char **str);
void			str_malloc_wildcard_check(t_mini *mini, t_wildcard *w, char *str);
void			wildcard_file_list_malloc_check(t_mini *mini, t_wildcard *w);
void			free_wildcard_double_pointer_first_part(t_mini *mini, t_wildcard*w);

#endif
