
#include "minishell.h"

static void	modify_env_array(t_mini *mini, char	*env_row)
{
	char	**temp_env;

	temp_env = string_array_push(mini->envp, env_row);
	if (!temp_env)
	{
		free(env_row);
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	if (mini->envp)
	{
		free(mini->envp);
		mini->envp = NULL;
	}
	mini->envp = temp_env;
	return ;
}

/**
 * Replaces the pointer inside the array of pointers if it starts with a given key
 * @param formated_env_key is the key with the equal sign
 * @param env_row is the entire env row with variable and path
 * @return - mini->last_return, otherwise nothing, it replaces the env row or adds.
 *
 * @return - NULL if malloc error
 * @note frees the env_row at the end
 * @note mainly used in execution
 */
int	set_env(t_mini *mini, char *formated_env_key, char *env_entry)
{
	int		i;

	i = 0;
	while (mini->envp[i])
	{
		if (start_with(mini->envp[i], formated_env_key))
		{
			free(mini->envp[i]);
			mini->envp[i] = env_entry;
			mini->last_return = 0;
			return (mini->last_return);
		}
		i++;
	}
	free(formated_env_key);
	modify_env_array(mini, env_entry);
	mini->last_return = 0;
	return (mini->last_return);
}
