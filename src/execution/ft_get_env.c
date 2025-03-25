
#include "minishell.h"

char	*ft_get_env(t_mini *mini, char	*var_name)
{
	size_t	var_length;
	char	*path_ref;
	char	*value_copy;

	var_length = ft_strlen(var_name);
	path_ref = string_array_find_string(mini->envp, var_name);
	if (!path_ref)
		return (NULL);
	value_copy = ft_strdup(path_ref + var_length + 1);
	if (!value_copy)
	{
		mini->last_return = MALLOC_ERROR;
		return (NULL);
	}
	return (value_copy);
}
