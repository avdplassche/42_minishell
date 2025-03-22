#include "minishell.h"

char	*ft_sized_strdup(char *s, int size)
{
	int		i;
	char	*dest;

	i = -1;
	dest = malloc((sizeof(char)) * (size + 1));
	if (!dest)
		return (NULL);
	while (s[++i])
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}