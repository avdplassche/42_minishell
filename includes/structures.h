
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


typedef struct s_file
{
	char		*path_name;
	int			type;
	char		*eof;
}				t_file;

/** A structure containing command's 'token'
 * @param command the name of the binary to execute
 * @param pathname path of the command (needed for execve)
 * @param type BUILTIND if in builtins dir, USER if in PATH, else, UNVALID
 * @param args arguments given to the binary
 * @param id id of the command (1 == first exec)
 * @param file struct containning file name + type containing all redirections
 * @param cmd_position where is located the cmd compared to the
 */
typedef struct s_cmd
{
	char		*command;
	char		*path;
	int			type;
	char		**args;
	int			arg_amount;
	int			id;
	t_file		*file;
	int			redir_amount;
	int			cmd_position;
	int			error;
}				t_cmd;

typedef struct s_quote
{
	int			sgl;
	int			dbl;
}				t_quote;
