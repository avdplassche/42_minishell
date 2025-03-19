
#include "minishell.h"

void	string_array_print(char **string_array)
{
	int	i;

	i = 0;
	while (string_array[i])
	{
		printf("%s\n", string_array[i]);
		i++;
	}
}
