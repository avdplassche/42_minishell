
#include "minishell.h"

void	print_string_array(char **string_array)
{
	int	i;

	i = 0;
	while (string_array[i])
	{
		printf("%s\n", string_array[i]);
		i++;
	}
}
