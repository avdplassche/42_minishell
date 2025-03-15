
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include "enum.h"
# include "structures.h"

#define BUILTINS_STRING "cd,env,exit,export,pwd,unset"
#define SPACES " 	\n"
#define BUILTIN_AMOUNT 6
#define BUFFER_SIZE 1
#define DEBUGG_PARSING 1
#define TEST_MODE 1
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define GREENBG "\033[42m"
# define REDBG "\033[41m"


/* * * * * * * * * *INIT * * * * * * * * * */

int			init_mini(t_mini *mini, char **envp);
int			count_cmd(t_mini *mini);

/* * * * * * * * * PARSING * * * * * * * * */

int			parsing(t_mini *mini, t_cmd *cmd);

int			get_envp_index(t_mini *mini, char *variable);
char		*translate_dollar_sign(t_mini *mini, char *temp, int sub_index);
int			need_dollar_substitution(char *str);
int			handle_dollar_sign(t_mini *mini, t_cmd *cmd);

int			is_valid_quote(t_mini *mini);
void		quote_enclosure_handle(char c, t_quote *quote);
int			strlen_quote_cleaned_command(char *str);
char		*clean_command_quotes(char *str);
char		*clean_envp_quotes(char *str);
char		last_quote(char *str, int i);


int			fill_cmd_structure(t_mini *mini, t_cmd *cmd);
char		*get_cmd_bin(t_mini *mini);
int			get_cmd_type(t_mini *mini, t_cmd *cmd);
int			get_cmd_args(t_mini *mini, t_cmd *cmd, int index);
int			get_cmd_redirection(t_mini *mini, t_cmd *cmd, int index);

/* * * * * * * * * EXECUTION * * * * * * * * */

void	exec_mini(t_mini *mini, t_cmd *cmd);

/* * * * * * * * * BUILTINS * * * * * * * * */

int			pwd();

/* * * * * * * * * * FREE * * * * * * * * * */

void		free_double_pointer(char **str);

/* * * * * * * * * ERRORS * * * * * * * * * */

int			is_valid_pipes(t_mini *mini);
int			is_valid_redirections(t_mini *mini);

/* * * * * * * * * *PRINT * * * * * * * * * */

void		print_unexpected_token(char *token);
void		print_char_table(char **string, char *name);
void		print_string(char *string, char *name);
void		print_cmd(t_cmd cmd, char *cmd_line);

void		print_quote_statement_debug(t_mini *mini, int i, t_quote *q);
void		debug_parsing_print(t_mini *mini, t_cmd *cmd);

/* * * * * * * * * *UTILS * * * * * * * * * */

				// LIBFT //

int			ft_atoi(char *str);
char		**ft_split(char *s, char c);
char		*ft_strchr(char *s, int c);
char		*ft_strdup(char *s1);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *s);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strnstr(char *haystack, char *needle, size_t len);
char		*ft_strtrim(char *s1, char *set);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		*ft_calloc(size_t count, size_t size);

				// GNL //

char		*get_next_line(int fd);

				// XTRA //

bool		contain_char(char *s, char c);
bool		contain_quotes(char *s);
char		*enquote_str(char *str, int q);
int			contain_string_at_specific_index(char *haystack, char *needle, int i);
bool		is_space(char c);
int			is_only_spaces(char *s);
char		*epurstring(char *src);
int			is_quote(char c);
int			is_angle_bracket(char c);

#endif
