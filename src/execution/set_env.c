
#include "minishell.h"

/**
 * Replaces the pointer inside the array of pointers if it starts with a given key
 * @parenv_rows the struct mini (cmd is not needed here)
 * @param env_key is
 * @return - the new string with the equal sign "PATH=""
 *
 * @return - NULL if malloc error
 * @note mainly used in execution
 */
int	set_env(t_mini *mini, char *env_key, char *env_row)
{
	int	i;

	i = 0;
	while (mini->envp[i])
	{
		if (start_with(mini->envp[i], key))
		{
			free(mini->envp[i]);
			mini->envp[i] = env_row;
			DEBUG("mini->envp[i] is worth %s", mini->envp[i]);
			mini->last_return = 0;
			return (0);
		}
		i++;
	}
	//string push if it does not work
	free(env_row);
	mini->last_return = CMD_NOT_FOUND;
	return (CMD_NOT_FOUND);
}
