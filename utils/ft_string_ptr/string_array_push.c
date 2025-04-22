//string array len and malloc + 2
//count the new element and the NULL because it is an array of string 
//memcpy i

#include "minishell.h"

char	**string_array_push(char **original_arr, char *new_ptr)
{
	char	**big_array;
	char	**current;
	int		original_len;
	int		i;

	if (!*original_arr)
	{
		big_array = ft_calloc(2, sizeof(char *));
		if (!big_array)
			return (NULL);
		current = big_array;
		*current = ft_strdup(new_ptr);
		*(current + 1) = NULL;
		return (big_array);
	}
	else
	{
		original_len = string_array_len(original_arr);
		big_array = ft_calloc(original_len + 2, sizeof(char *));
		if (!big_array)
		{
			return (NULL);
		}
	}
	i = 0;
	while (original_arr[i])
	{
		big_array[i] = ft_strdup(original_arr[i]);
		free_string_ptr(&original_arr[i]);
		if (!big_array[i])
		{
			while (--i >= 0)
				free(big_array[i]);
			free(big_array);
			return (NULL);
		}
		i++;
	}
	big_array[i] = ft_strdup(new_ptr);
	if (!big_array[i])
	{
		while (--i >= 0)
			free(big_array[i]);
		free(big_array);
		return (NULL);
	}
	free_string_ptr(&new_ptr);
	return (big_array);
}
