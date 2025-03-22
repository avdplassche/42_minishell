
#include "minishell.h"

char	*get_current_workdir(t_mini *mini)
{
	char	buffer[PATH_MAX + 1];
	char	*new_cwd;
	
	new_cwd = getcwd(buffer, PATH_MAX + 1);
	if (!new_cwd)
	{
		mini->last_return = MALLOC_ERROR;
		return (NULL);
	}
	return (new_cwd);
}
