
#include "minishell.h"

/*
	here i am creating enough space for "PATH=\0", this is the string i am trying to find
*/
char *create_key_format(char *variable, int variable_len)
{
	char	*key_format_variable;
	char	*current;
	
	key_format_variable = (char *)malloc(sizeof(char) * (variable_len + 2));
	if (!key_format_variable)
		return (NULL);
	current = key_format_variable;
	while (*variable)
	{
		*current = *variable;
		current++;
		variable++;
	}
	*current = '=';
	current++;
	*(current) = '\0';
	return (key_format_variable);
}

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
	search_str = create_key_format(string_to_find, variable_len);
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
