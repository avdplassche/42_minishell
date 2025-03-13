

#include "minishell.h"

enum	e_standard
{
		STDIN = 0,
		STDOUT = 1,
		STDERR = 2,
};

enum	e_error
{
		MALLOC_ERR = -1,


};

enum	e_redirections
{
		PIPE = 1,
		IN_REDIR = 2,
		OUT_REDIR = 3,
		HERE_DOC = 4,
		OUT_APPEND = 5,
};

enum	e_command
{
		UNVALID = -1,
		USER = 0,
		BUILTIN = 1,
};
