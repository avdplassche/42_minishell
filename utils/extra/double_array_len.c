
#include "minishell.h"

int	double_array_len(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}
