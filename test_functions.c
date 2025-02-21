

#include "includes/minishell.h"

/**
 * this file is here to test if created functions are working as intended
 *
 */
int	check_line_first_char(char c)
{
	char	*set;
	int		i;

	i = -1;
	set = "|<>?$#%";
	while (set[++i])
		if (c == set[i])
			return (0);
	return (1);
}

int main (void)
{
	printf("%d\n", check_line_first_char('%'));
}
