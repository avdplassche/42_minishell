
#include "minishell.h"

/*
	1. send the variable to become a key format (PATH --> PATH=)
	2. strcmp inside the char **env until found
	3. return the pointer that holds the address of the given path 
*/
char	*string_array_find_key(char **string_array, char *string_to_find)
{
	int		i;
	char	*search_str;
	size_t	variable_len;

	if (string_array == NULL || string_to_find == NULL)
		return (NULL);
	i = 0;
	variable_len = ft_strlen(string_to_find);
	search_str = create_env_key_format(string_to_find, variable_len);
	if (!search_str)
		return (NULL);
	while (string_array[i])
	{
		if (start_with(string_array[i], search_str))
		{
			free(search_str);
			search_str = NULL;
			return (string_array[i]);
		}
		i++;
	}
	free(search_str);
	search_str = NULL;
	return (NULL);
}
