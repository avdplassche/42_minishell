
#include "minishell.h"

static void	modify_env_array(t_mini *mini, char	*env_entry)
{
	char	**temp_env;
	char	*new_env_entry;

	new_env_entry = ft_strdup(env_entry);
	if (!new_env_entry)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	temp_env = string_array_push(mini->envp, new_env_entry);
	if (!temp_env)
	{
		free(new_env_entry);
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	if (mini->envp)
	{
		free(mini->envp);
	}
	mini->envp = temp_env;
	return ;
}

/**
 * Replaces the pointer inside the array of pointers if it starts with a given key
 * @param env_key is the key with the equal sign
 * @param env_row is the entire env row with variable and path
 * @return - mini->last_return, otherwise nothing, it replaces the env row or adds.
 *
 * @return - NULL if malloc error
 * @note frees the env_row at the end
 * @note mainly used in execution
 */
int	set_env(t_mini *mini, char *env_key, char *env_entry)
{
	int		i;

	i = 0;
	while (mini->envp[i])
	{
		if (start_with_identifier(mini->envp[i], env_key))
		{
			free_string_ptr(&mini->envp[i]);
			mini->envp[i] = ft_strdup(env_entry);
			if (!mini->envp[i])
			{
				mini->last_return = MALLOC_ERROR;
			}
			mini->last_return = 0;
			return (mini->last_return);
		}
		i++;
	}
	modify_env_array(mini, env_entry);
	mini->last_return = 0;
	return (mini->last_return);
}
