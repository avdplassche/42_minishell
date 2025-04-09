
#include "minishell.h"

/** Frees char ** variables
 */
void	free_string_array(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_pathnames(t_cmd cmd)
{
	int	i;

	i = 0;
	// DEBUG("Redir Amount : %d\n\n", cmd->redir_amount);
	while (i < cmd.redir_amount)
	{
		free(cmd.redir[i].name);
		i++;
	}
	free(cmd.redir);
}
