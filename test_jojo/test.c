
#include "../includes/minishell.h"

static char *build_search_str(char *string_to_find, int variable_len)
{
	char	*search_str;
	
	search_str = (char *)malloc(sizeof(char) * variable_len + 2);
	if (!search_str)
		return (NULL);
	ft_strcpy(search_str, string_to_find); // a copy of the string is made, there are still 0s because src is smaller than dest 
	search_str[variable_len] = '=';
	search_str[variable_len + 1] = '\0';
	return (search_str);
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
	search_str = build_search_str(string_to_find, variable_len);
	if (!search_str)
		return (NULL);
	while (string_array[i])
	{
		if (start_with(string_array[i], search_str))
		{
			free(search_str);
			search_str = NULL;
			return (string_array[i] + variable_len + 1);
		}
		i++;
	}
	free(search_str);
	search_str = NULL;
	return (NULL);
}

int main(int argc, char **argv, char **env)
{
	t_mini	mini;
	(void)argc;
	(void)argv;
	char	*path;

	mini.envp = env;
	path = find_string_in_array(mini.envp, "LS_COLORS");
	if (!path)
		return (1);
	printf("%s\n", path);
	return (0);
}
