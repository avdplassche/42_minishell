
#include "minishell.h"

static char	*get_new_array(char	**array)
{
	int		len;
	int		i;
	
	len = 0;
	i = 0;
	while (array[i])
	{
		len += ft_strlen(array[i]);
		i++;
	}
	return (ft_calloc((len + 1), sizeof(char)));
}

static char *string_add(char *dst, char *content)
{
	while (*content)
		*(dst++) = *(content++);
	return (dst);
}

char	*string_array_join(char	**array)
{
	char	*new_array;
	char	*current;

	new_array = get_new_array(array);
	if (!new_array)
		return (NULL);
	current = new_array;
	while (*array)
		current = string_add(current, *(array++));
	return (new_array);
}
