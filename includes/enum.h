
#include "minishell.h"

/* typedef enum e_whatever         < ---- NORM for enum
{
	ONE,
	TWO,
	THREE
}	t_whatever; */

typedef enum e_standard
{
			STDIN = 0,
			STDOUT = 1,
			STDERR = 2,
}			t_standard;

typedef enum e_error
{
			MALLOC_ERROR = 1,
			CMD_NOT_FOUND = 2,
			PIPE_ERROR = 3,
			FORK_ERROR = 4,
			DUP_ERROR = 5,
}			t_error;

typedef enum e_redirections
{
			IN_REDIR,
			OUT_REDIR,
			HERE_DOC,
			OUT_APPEND,
}			t_redirections;

typedef enum e_command
{
			INVALID = -1,
			USER = 0,
			BUILTIN = 1,
}			t_command;
