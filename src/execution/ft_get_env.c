
#include "minishell.h"

char	*ft_get_env(t_mini *mini, char	*var_name)
{
	size_t	var_length;
	char	*full_path;
	char	*full_path_copy;

	var_length = ft_strlen(var_name);
	full_path = string_array_find_string(mini->envp, var_name);
	if (!full_path)
		return (NULL);
	full_path_copy = strdup(full_path + var_length + 1);
	if (!full_path_copy)
	{
		free(full_path);
		mini->last_return = MALLOC_ERROR;
		return (NULL);
	}
	return (full_path_copy);
}
