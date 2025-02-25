


#include "../includes/minishell.h"


int	ft_is_only_spaces(char *s)
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