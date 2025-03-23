
#include "minishell.h"

char	*get_new_env_row(t_mini *mini, char *env_key, char *new_path)
{
	char	*env_row;
	
	env_row = malloc((ft_strlen(env_key) + ft_strlen(new_path) + 1));
	if (!env_row)
	{
		mini->last_return = MALLOC_ERROR;
		free(new_path);
		return (NULL);
	}
	string_build(&env_row, env_key, new_path);
	return (env_row);
}
