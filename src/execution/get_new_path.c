
#include "minishell.h"

char	*get_new_path(t_mini *mini, char *env_key, char *new_path)
{
	char	*full_new_path;
	
	full_new_path = malloc((ft_strlen(env_key) + ft_strlen(new_path) + 1));
	if (!full_new_path)
	{
		mini->last_return = MALLOC_ERROR;
		free(new_path);
		return (NULL);
	}
	string_build(&full_new_path, env_key, new_path);
	return (full_new_path);
}
