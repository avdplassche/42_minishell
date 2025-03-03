
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "enum.h"
# include "structures.h"

#define BUILTINS_STRING "cd,echo,env,exit,export,pwd,unset"
#define BUILTIN_AMOUNT 7
#define BUFFER_SIZE 10
#define DEBUGG_PARSING 1
#define TEST_MODE 1




/* * * * * * * * * *INIT * * * * * * * * * */

int			init_mini(t_mini *mini, char **envp);
int			count_cmd(t_mini *mini);

/* * * * * * * * * PARSING * * * * * * * * */

int			parsing(t_mini *mini, t_cmd *cmd);

int			handle_dollar_sign(t_mini *mini, t_cmd *cmd);

int			is_valid_quote(t_mini *mini);


int			fill_cmd_structure(t_mini *mini, t_cmd *cmd);
char		*clean_quotes(t_cmd *cmd, char *str);
int			get_cmd_string(t_mini *mini, t_cmd *cmd);
int			get_cmd_type(t_mini *mini, t_cmd *cmd);
int			get_cmd_args(t_mini *mini, t_cmd *cmd_struct);




/* * * * * * * * * BUILTINS * * * * * * * * */




/* * * * * * * * * *PRINT * * * * * * * * * */

void		print_char_table(char **string, char *name);
void		print_string(char *string, char *name);
void		print_cmd(t_cmd cmd, char *cmd_line);

void		debug_parsing(t_mini *mini, t_cmd *cmd);

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
int			contain_string_at_specific_index(char *haystack, char *needle, int i);
bool		is_space(char c);
int			is_only_spaces(char *s);
char		*epurstring(char *src);
int			is_quote(char c);

#endif
