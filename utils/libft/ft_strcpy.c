
#include "minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	char	*cursor;

	if (dest == NULL || src == NULL)
		return (NULL);
	cursor = dest;
	while (*src)
	{
		*cursor = *src;
		cursor++;
		src++;
	}
	*cursor = '\0';
	return (dest);
}
