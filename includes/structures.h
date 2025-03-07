
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

/** A structure containing command's 'token'
 * @param command the name of the binary to execute
 * @param type BUILT if in builtins dir, BIN if in PATH, UNVALID else
 * @param args arguments given to the binary
 * @param id id of the command (1 == first exec)
 * @param filename file name if needed by the command line(needed for redir)
 * @param is_path bool to know if filename is a path or not
 * @param pipe will the command be redirected by a pipe ?
 * @param in_redir is there an input redirection in the command
 * @param out_redir is there an output redirection in the command
 * @param in_delimiter is there a delimiter in the command (<<)
 * @param out_appredir is there an out_appredir in the command (>>)
 */
typedef struct s_cmd
{
	char		*command;
	int			type;
	char		**args;
	int			id;
	char		*filename;
	int			pipe;
	int			in_redir_total;
	int			out_redir_total;
	int			in_delimiter_total;
	int			out_appredir_total;

	int			error;
}				t_cmd;

typedef struct s_quote
{
	int			sgl;
	int			dbl;
}				t_quote;
