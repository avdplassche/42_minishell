#include "minishell.h"

/** Find needle in haystack, starting at a specific index
 * @param haystack where to find needle
 * @param needle string to find in haystack
 * @param i index where to look at
 *
 * Ex : i = 5, strlen(needle) = 2, the function will scan haystack[5] and haystack[6]
 */
int	contain_string_at_specific_index(char *haystack, char *needle, int i)
{
	int	j;
	int	k;

	j = 0;
	k = ft_strlen(needle);
	while (haystack[i] && j < k)
	{
		if (haystack[i] != needle[j])
			return (0);
		i++;
		j++;
	}
	if (j != k)
		return (0);
	return (1);
}

