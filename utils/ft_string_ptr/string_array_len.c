
#include "minishell.h"

/**
 * get the length of an array of pointers
 * @param str is the array of pointers you want the size of
 * @param variablelen is the length (int) of the variable
 * @return - size (type size_t) of the array of pointers
 */
size_t	string_array_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
