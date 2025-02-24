/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:52:23 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/24 17:07:47 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "enum.h"
# include "structures.h"

/* * * * * * * * * PARSING * * * * * * * * */

int			fill_cmd_structure(t_mini *mini, t_cmd *cmd_struct, int bin_count);

t_cmd		*parsing(t_mini *mini);



/* * * * * * * * * BUILTINS * * * * * * * * */



/* * * * * * * * * UTILS * * * * * * * * * */

				// LIBFT //

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
bool		is_space(char c);


#endif
