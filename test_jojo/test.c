
#include "../includes/minishell.h"

static char *build_search_str(char *string_to_find, int variable_len)
{
	char	*search_str;
	
	search_str = (char *)malloc(sizeof(char) * variable_len + 2);
	if (!search_str)
		return (NULL);
	ft_strcpy(search_str, string_to_find);
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
			return (string_array[i]);
		}
		i++;
	}
	free(search_str);
	search_str = NULL;
	return (NULL);
}

char	*ft_get_env(t_mini *mini, char	*var_name)
{
	size_t	var_length;
	char	*full_path;
	
	var_length = ft_strlen(var_name);
	full_path = find_string_in_array(mini->envp, var_name);
	if (!full_path)
		return (NULL);
	return (full_path + var_length + 1);
}

int main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*s;
	char	**test;
	(void)argc;
	(void)argv;

	mini.envp = env;
	s = ft_get_env(&mini, "PATH");
	if (!s)
	{
		return (1);
	}
	//printf("%s\n", s);
	test = ft_split(s, ':');
	print_string_array(test);
	return (0);
}
