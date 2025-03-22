
#include "minishell.h"

/**
 * get the length of an array of pointers
 * @param str is the array of pointers you want to print to the standard out
 * @return - void, prints in terminal
 */
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
