/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:38:11 by jrandet           #+#    #+#             */
/*   Updated: 2025/03/25 15:14:39 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_fd_backup
{
	int	stdin_backup;
	int	stdout_backup;
	int	stderr_backup;
}	t_fd_backup;

typedef union u_pipe_ends
{
	int	fildes[2];
	struct
	{
		int		read;
		int		write;
	};	
}			t_pipe_ends;


typedef struct s_redir
{
	char	*pathname;
	char	*eof; //maybe delete
	int		type;
}	t_redir;

typedef struct s_quote
{
	int	sgl;
	int	dbl;
}	t_quote;

/** A structure containing minishell related variables
 * @param envp local environment variables (execve's 3rd parameter for ex)
 * @param builtins list of builtins functions (present in builtins dir)
 * @param paths list of path directories to look for binaries
 * @param line current prompt to work with
 * @param cmd_amount amount of commands in the command_line (also amount of pipes)
 * @param last_return sig return of the last cmd (needed for $?)
 * @param cursor used to remember where we stopped the parsing
 * @param error to be configured
 */
typedef struct s_mini
{
	char		**envp;
	char		**builtins;
	char		**paths;
	char		*line;
	int			cmd_amount;
	int			last_return;
	int			cursor;
	bool		error;
	t_fd_backup	*fd_backup;
}				t_mini;

/** A structure containing command's 'token'
 * @param command the name of the binary to execute
 * @param path path of the command (needed for execve)
 * @param type BUILTIND if in builtins dir, USER if in PATH, else, UNVALID
 * @param echo_n_index if command = echo -n -n gives the index of the first argument after -n in this case 3
 * @param args arguments given to the binary (needed for execve)
 * @param arg_amount amount of arguments in the command
 * @param id id of the command (1 == first exec) // Is it needed ?
 * @param file struct containning file name + type containing all redirections
 * @param redir type of the redirection and path to the file
 * @param error not set yet
 */
typedef struct s_cmd
{
	char		*command;
	char		*path;
	int			type;
	int			echo_n_index;
	char		**args;
	int			arg_amount;
	int			id;
	t_redir		*redir;
	int			redir_amount;
	int			error;
	t_pipe_ends	pipe_in;
	t_pipe_ends	pipe_out;
	pid_t		pid;
}				t_cmd;

/** A pointer to function for the builtin function
 * @param t_builtin_func contains the signature of all the builtin functions
 */
typedef int (*t_builtin_func)(t_cmd *, t_mini *);


typedef struct s_wildcard
{
	char			*dirname;
	char			*token;
	struct dirent	*s_dir;
	char			*prefix;
	char			*suffix;
	bool			current;
}					t_wildcard;