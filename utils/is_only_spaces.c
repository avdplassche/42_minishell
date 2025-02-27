


#include "../includes/minishell.h"

/** Check if string is composed of spaces only
 * @return - 1 if only space
 * @return - 0 if there is other characters
 */
int	is_only_spaces(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!(is_space(s[i])))
			return (0);
	}
	return (1);
}
