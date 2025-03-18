
#include "minishell.h"

int	start_with(char *string, char *start_string)
{
	int	i;

	i = 0;
	while (string[i] && start_string[i])
	{
		if (string[i] != start_string[i])
			return (0);
		i++;
	}
	return (1);
}
