
#include "minishell.h"

typedef struct s_fd_backup
{
	int	stdin_backup;
	int	stdout_backup;
}	t_fd_backup;

typedef union u_pipefd
{
	int	fildes[2];
	struct
	{
		int		read;
		int		write;
	};	
}			t_pipefd;


typedef struct s_redir
{
	char				*name;
	t_redirections		type;
	int					heredoc_fd;
}	t_redir;

typedef struct s_quote
{
	int	sgl;
	int	dbl;
}	t_quote;

typedef struct s_alloc
{
	char			*line_out;
	char			*prefix;	
	char			*suffix;
	char			*number;
	char			*temp;
	char			*var_name;
	char			*var_env;
	char			*var_value;
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
}					t_wildcard;

typedef struct s_cmd t_cmd;

/** A structure containing minishell related variables
 * @param envp local environment variables (execve's 3rd parameter for ex)
 * @param builtins list of builtins functions (present in builtins dir)
 * @param paths list of path directories to look for binaries
 * @param line current prompt to work with
 * @param cmd_amount amount of commands in the command_line (also amount of pipes)
 * @param last_return sig return of the last cmd (needed for $?)
 * @param cursor used to remember where we stopped the parsing
 * @param error to be configured
 * @param fdin 
 */
typedef struct s_mini
{
	char		**envp;
	char		**export;
	char		**builtins;
	char		**paths;
	char		*line;
	int			cmd_count;
	int			last_return;
	int			cursor;
	bool		error;
	t_fd_backup	*fd_backup; 
	t_pipefd	*pipes; //array of pipes
	t_cmd		*cmd; // cmd in a single cmd operation, and then i renamed it to cmd_array in multicmd operations 
	t_wildcard	w;
	bool		should_exit;
}				t_mini;

/** A structure containing command's 'token'
 * @param command the name of the binary to execute
 * @param path path of the command (needed for execve)
 * @param export is it an export command
 * @param type BUILTIND if in builtins dir, USER if in PATH, else, UNVALID
 * @param echo_n_index if command = echo -n -n gives the index of the first argument after -n in this case 3
 * @param args arguments given to the binary (needed for execve)
 * @param arg_amount amount of arguments in the command
 * @param id id of the command (1 == first exec) // Is it needed ?
 * @param file struct containning file name + type containing all redirections
 * @param redir type of the redirection and path to the file
 * @param error not set yet
 * @param pid_t is the pid of the process 
 * @param pipe_in is the pipe on the left of the command
 * @param pipe_out is the pipe on the right of the command
 * 
 */
typedef struct s_cmd
{
	char			*command;
	char			*path;
	int				type;
	int				echo_n_index;
	char			**args;
	int				arg_amount;
	int				id;
	t_redir			*redir;
	int				redir_amount;
	int				heredoc_amount;
	int				error;
	pid_t			pid;
	t_pipefd		*pipe_in;
	t_pipefd		*pipe_out;
	int				needs_cleanup;
}					t_cmd;

/** A pointer to function for the builtin function
 * @param t_builtin_func contains the signature of all the builtin functions
 */
typedef int (*t_builtin_func)(t_mini *, t_cmd *);


