//string array len and malloc + 2
//count the new element and the NULL because it is an array of string 
//memcpy i

#include "minishell.h"

char	**string_array_push(char **original_arr)
{
	char	**new_big_arr;

	new_big_arr = (char **)malloc(sizeof(char *) * (string_array_len(original_arr + 2)));
	if (!new_big_arr)
	{
		return (NULL);
	}
	return (new_big_arr);
}
