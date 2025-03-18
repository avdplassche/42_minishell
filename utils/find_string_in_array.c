
#include "../includes/minishell.h"

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
	
	
	
}