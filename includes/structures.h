
#include "minishell.h"


/** A structure containing minishell related variables
 * @param envp local environment variables (execve's 3rd parameter for ex)
 * @param builtins list of builtins functions (present in builtins dir)
 * @param paths list of path directories to look for binaries
 * @param current_line current prompt to work with
 * @param last_return sig return of the last cmd (needed for $?)
 * @param error to be configured
 */
typedef struct s_mini
{
	char		**envp;
	char		**builtins;
	char		**paths;
	char		*current_line;
	int			total_cmd;
	int			last_return;
	bool		error;
}				t_mini;

/** A structure containing command's 'token'
 * @param command the name of the binary to execute
 * @param type BUILT if in builtins dir, BIN if in PATH, UNVALID else
 * @param args arguments given to the binary
 * @param filename file name if needed by the command (needed for redir)
 * @param file_path bool to know if filename is a path or not
 * @param total_cmd amount of commands in the command_line (also amount of pipes)
 * @param id id of the command (1 == first exec)
 * @param in_redir is there an input redirection in the command
 * @param out_redir is there an output redirection in the command
 * @param delimiter is there a delimiter in the command (<<)
 * @param out_appredir is there an out_appredir in the command (>>)
 * @param index used to remember where we stopped the parsing
 */
typedef struct s_cmd
{
	char		*command;
	int			type;
	char		**args;
	char		*filename;
	bool		file_path;
	int			total_cmd;
	int			id;
	bool		in_redir;
	bool		out_redir;
	bool		delimiter;
	bool		out_appredir;
	int			index; //maybe rename by i ?
	int			error;
}				t_cmd;
