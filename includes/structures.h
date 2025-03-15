
#include "minishell.h"


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
}				t_mini;


typedef struct s_redir
{
	char		*pathname;
	char		*eof;
	int			type;
}				t_redir;

/** A structure containing command's 'token'
 * @param command the name of the binary to execute
 * @param path path of the command (needed for execve)
 * @param type BUILTIND if in builtins dir, USER if in PATH, else, UNVALID
 * @param args arguments given to the binary (needed for execve)
 * @param arg_amount amount of arguments in the command
 * @param id id of the command (1 == first exec) // Is it needed ?
 * @param file struct containning file name + type containing all redirections
 * @param redir_amount amount of redirections, needed for malloc
 * @param error not set yet
 */
typedef struct s_cmd
{
	char		*command;
	char		*path;
	int			type;
	char		**args;
	int			arg_amount;
	int			id;
	t_redir		*redir;
	int			redir_amount;
	int			error;
}				t_cmd;

typedef struct s_quote
{
	int			sgl;
	int			dbl;
}				t_quote;
