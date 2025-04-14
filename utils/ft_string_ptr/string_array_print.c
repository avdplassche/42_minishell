
#include "minishell.h"

static int	contains_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/**
 * get the length of an array of pointers
 * @param str is the array of pointers you want to print to the standard out
 * @return - void, prints in terminal
 */
void	string_array_print(t_cmd *cmd, char **string_array)
{
	int	i;

	i = 0;
	while (string_array[i])
	{
		if (cmd->is_export)
		{
			printf("declare -x %s\n", string_array[i]);
		}
		else if (contains_equal(string_array[i]) && !cmd->is_export)
		{
			printf("%s\n", string_array[i]);
		}
		i++;
	}
}
