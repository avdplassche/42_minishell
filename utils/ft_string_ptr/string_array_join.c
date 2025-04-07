
#include "minishell.h"

static char	*get_new_array(char	**array)
{
	int		len;
	int		i;
	char	*new_array;
	
	len = 0;
	i = 0;
	while (array[i])
	{
		len += ft_strlen(array[i]);
		i++;
	}
	new_array = malloc(sizeof(char) * (len + 1));
	if (!new_array)
	{
		return (NULL);
	}
	return (new_array);
}

char	*string_array_join(char	**array)
{
	char	*new_array;
	char	*current;
	int		i;
	int		j;

	new_array = get_new_array(array);
	current = new_array;
	i = 0;
	j = 0;
	while (array[i])
	{
		j = 0;
		while(array[i][j])
		{
			*current = array[i][j];
			current++;
			j++;
		}
		i++;
	}
	*current = '\0';
	return (new_array);
}
