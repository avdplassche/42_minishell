
#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	char	*testpointer;

	testpointer = s;
	while (n--)
		*testpointer++ = 0;
}
