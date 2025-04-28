/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:57:27 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/28 10:33:36 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

// typedef struct s_fd_backup
// {
// 	int				stdin_backup;
// 	int				stdout_backup;
// }	t_fd_backup;

typedef union u_pipefd
{
	int				fildes[2];
	struct
	{
		int			read;
		int			write;
	};	
}			t_pipefd;

typedef struct s_redir
{
	char			*name;
	int				type;
	int				heredoc_fd;
}					t_redir;

typedef struct s_quote
{
	int				sgl;
	int				dbl;
}					t_quote;

typedef struct s_alloc
{
	char			*line_out;
	char			*prefix;
	char			*suffix;
	char			*number;
	char			*temp;
	char			*var_name;
	t_quote			q;
}					t_alloc;

typedef struct s_wildcard
{
	char			*wildcard;
	char			*dirname;
	char			*token;
	struct dirent	*s_dir;
	char			*prefix;
	char			*suffix;
	char			*temp;
	char			**file_list;
	bool			current;
	int				file_amount;
	char			*line_suffix;
}					t_wildcard;

typedef struct s_cmd	t_cmd;

typedef struct s_mini
{
	char			**envp;
	char			**export;
	char			**builtins;
	char			**paths;
	char			*line;
	int				cmd_count;
	int				last_return;
	int				cursor;
	bool			error;
	int				stdin_backup;
	int				stdout_backup;
	t_pipefd		*pipes; //array of pipes
	t_cmd			*cmd; // cmd in a single cmd operation, and then i renamed it to cmd_array in multicmd operations
	t_wildcard		w;
	bool			should_exit;
}					t_mini;

/** A structure containing command's 'token'
 * @param command the name of the binary to execute
 * @param path path of the command (needed for execve)
 * @param type BUILTIND if in builtins dir, USER if in PATH, else, UNVALID
 * @param args arguments given to  the binary (needed for execve)
 * @param arg_amount amount of arguments in the command
 * @param id id of the command (1 == first exec) // Is it needed ?
 * @param file struct containning file name + type containing all redirections
 * @param redir type of the redirection and path to the file
 * @param pid_t is the pid of the process
 * @param pipe_in is the pipe on the left of the command
 * @param pipe_out is the pipe on the right of the command
 */
typedef struct s_cmd
{
	char			*command;
	bool			is_directory;
	int				error_access;
	char			*path;
	int				type;
	char			**args;
	int				arg_amount;
	int				id;
	t_redir			*redir;
	int				redir_amount;
	int				heredoc_amount;
	pid_t			pid;
	t_pipefd		*pipe_in;
	t_pipefd		*pipe_out;
	int				needs_cleanup;
	int				is_export;
}					t_cmd;

/** A pointer to function for the builtin function
 * @param t_builtin_func contains the signature of all the builtin functions
 */
typedef int	(*t_builtin_func)(t_mini *, t_cmd *);

#endif
