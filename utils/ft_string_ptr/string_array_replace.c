
#include "minishell.h"

void	string_array_replace(t_mini *mini, char	*env_key, char *path_replace)
{
	int	i;

	i = 0;
	while (mini->envp[i])
	{
		if (start_with(mini->envp[i], env_key))
		{
			free(mini->envp[i]);
			mini->envp[i] = path_replace;
			return ;
		}
		i++;
	}
	free(path_replace);
}
