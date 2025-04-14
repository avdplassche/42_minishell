#include "minishell.h"

int	is_valid_syntax(char *command)
{
	const char	set[7] = "&|><;()";
	int			i;

	i = -1;
	while (command[++i])
		if (!contain_char(set, command[i]))
			return (1);
	print_error("minishell: syntax error near unexpected token '%s'\n", command, 2);
	return (0);
}
