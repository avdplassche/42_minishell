
#include "minishell.h"

char	*get_current_workdir(t_mini *mini)
{
	char	*new_cwd;

	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
	{
		mini->last_return = MALLOC_ERROR;
		return (NULL);
	}
	return (new_cwd);
}
