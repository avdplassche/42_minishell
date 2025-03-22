#include "minishell.h"



int	is_only_specific_char(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != c)
			return (0);
	}
	return (1);
}
