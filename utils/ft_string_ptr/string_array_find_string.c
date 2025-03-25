
#include "minishell.h"

/**
 * search for a pointer in an array of pointer and return it if it is found.
 * @param string_array is the array of pointers to search in
 * @param string_to_find is the name of the variable, in this case "PATH"
 * @return pointer directly located in ENV DO NOT FREE THIS
 *
 * @return none, void
 * @note mainly used in execution 
 */
char	*string_array_find_string(char **string_array, char *string_to_find)
{
	int		i;
	char	*search_str;
	size_t	variable_len;

	if (string_array == NULL || string_to_find == NULL)
		return (NULL);
	i = 0;
	variable_len = ft_strlen(string_to_find);
	search_str = string_array_create_key(string_to_find, variable_len);
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
