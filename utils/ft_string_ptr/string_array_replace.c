
#include "minishell.h"

/**
 * Replaces the pointer inside the array of pointers if it starts with a given prefix
 * @param mini is the struct mini (cmd is not needed here)
 * @param env_key is 
 * @return - the new string with the equal sign "PATH=""
 *
 * @return - NULL if malloc error 
 * @note mainly used in execution 
 */
int	string_array_replace(t_mini *mini, char *prefix, char *new_value)
{
	int	i;

	DEBUG("the path to replace with is %s\n", new_value);
	i = 0;
	while (mini->envp[i])
	{
		if (start_with(mini->envp[i], prefix))
		{
			free(mini->envp[i]);
			mini->envp[i] = new_value;
			DEBUG("mini->envp[i] is worth %s", mini->envp[i]);
			mini->last_return = 0;
			return (0);
		}
		i++;
	}
	free(new_value);
	mini->last_return = CMD_NOT_FOUND;
	return (CMD_NOT_FOUND);
}
