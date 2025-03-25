
#include "minishell.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while ((9 <= str[i] && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nb = nb + str[i] - 48;
		if ('0' <= str[i + 1] && str[i + 1] <= '9')
			nb *= 10;
		i++;
	}
	return (nb * sign);
}
/*
int main(void)
{
	printf("%d", ft_atoi("  -214"));
	return (0);
}
*/
