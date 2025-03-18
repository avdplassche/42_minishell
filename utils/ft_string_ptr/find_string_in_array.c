
/*#include "../includes/minishell.h"

static int start_with(char *string, char *start_string)
{
	int	i;

	i = 0;
	while (string[i] && start_string[i])
	{
		if (string[i] != start_string[i])
			return (0);
		i++;
	}
	return (1);
}

char	*find_string_in_array(char **string_array, char *string_to_find)
{
	int		i;
	char	*search_str;
	size_t	variable_len;

	if (string_array == NULL || string_to_find == NULL)
		return (NULL);
	i = 0;
	variable_len = ft_strlen(string_to_find);
	search_str = (char *)malloc(sizeof(char) * variable_len + 2);
	if (!search_str)
	{
		return (NULL);
	}
	ft_strcpy(search_str, string_to_find); // a copy of the string is made, there are still 0s because src is smaller than dest 
	search_str[variable_len] = '=';
	*(variable_len + 1) = 
}*/