

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
		PIPE = '|',
		IN_REDIR = '<',
		OUT_REDIR = '>',
};

enum	e_command
{
		UNVALID = -1,
		USER = 0,
		BUILTIN = 1,
};

enum	e_unexpected_token
{
		UNEXPECTED_IN_REDIR = -1,
		UNEXPECTED_OUT_REDIR = -2,
};