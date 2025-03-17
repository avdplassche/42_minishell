
#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int main()
{
	char	str[] = "hello";
	char	str2[] = "hella";

	printf("the difference is %d\n", ft_strcmp(str, str2));
	return (0);
}