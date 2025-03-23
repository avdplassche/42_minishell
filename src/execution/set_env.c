
#include "minishell.h"

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
int	set_env(t_mini *mini, char *env_key, char *env_row)
{
	int	i;

	i = 0;
	while (mini->envp[i])
	{
		if (start_with(mini->envp[i], env_key))
		{
			free(mini->envp[i]);
			mini->envp[i] = env_row;
			DEBUG("mini->envp[i] is worth %s\n", mini->envp[i]);
			mini->last_return = 0;
			return (0);
		}
		i++;
	}
	//string push if it does not work
	free(env_row);
	mini->last_return = CMD_NOT_FOUND;
	return (mini->last_return);
}
