

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

// enum	e_redirections
// {
// 		PIPE = '|',
// 		IN_REDIR = '<',
// 		OUT_REDIR = '>',
// };

enum	e_binary
{
		UNVALID = -1,
		USER = 0,
		BUILTIN = 1,
};
