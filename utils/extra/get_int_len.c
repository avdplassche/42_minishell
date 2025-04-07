#include "minishell.h"

int	get_int_len(int n)
{
	int	count;

	count = 1;
	while (n / 10 > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

