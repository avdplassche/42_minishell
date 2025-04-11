//string array len and malloc + 2
//count the new element and the NULL because it is an array of string 
//memcpy i

#include "minishell.h"

char	**string_array_push(char **original_arr, char *new_ptr)
{
	char	**big_array;
	int		original_len;
	int		i;

	original_len = string_array_len(original_arr);
	big_array = malloc(sizeof(char *) * (original_len + 1 + 1));
	if (!big_array)
	{
		return (NULL);
	}
	i = 0;
	while (original_arr[i])
	{
		big_array[i] = original_arr[i];
		i++;
	}
	big_array[i] = new_ptr;
	big_array[i + 1] = NULL;
	return (big_array);
}
