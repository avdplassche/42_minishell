
#include "minishell.h"

/**
 * To create the key format of the variable in the env array
 * @param mini
 * @param var_name like PATH
 * @return - a copy of the path without "PATH=""
 *
 * @return - NULL if malloc error 
 * @note the path reference found with s
 */
char	*ft_get_env(t_mini *mini, t_cmd *cmd, char	*var_name)
{
	size_t	var_length;
	char	*path_ref;
	char	*value_copy;

	if (!mini->envp || !*mini->envp || !var_name)
		return (NULL);
	var_length = ft_strlen(var_name);
	path_ref = string_array_find_identifier(mini->envp, var_name);
	if (!path_ref)
		return (NULL);
	value_copy = ft_strdup(path_ref + var_length + 1);
	if (!value_copy)
	{
		mini->last_return = MALLOC_ERROR;
		exit_minishell(mini, cmd);
	}
	return (value_copy);
}
