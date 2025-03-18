#include "../includes/minishell.h"

/**
 * To know there is quote in a specific string
 * @param s a string
 * @return - 1 if quote
 * @return - 0 if no quote
*/
bool	contain_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (1);
	}
	return (0);
}
