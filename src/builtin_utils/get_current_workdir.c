
#include "minishell.h"

char	*get_current_workdir(t_mini *mini)
{
	char	*new_cwd;

	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
	{
		if (errno == ENOMEM)
			mini->last_return = MALLOC_ERROR;
		else
			mini->last_return = 1;
		return (NULL);
	}
	return (new_cwd);
}
