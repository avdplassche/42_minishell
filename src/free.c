#include "../includes/minishell.h"


void	free_cmd(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < mini->cmd_amount)
	{
		if (cmd[i].command != NULL)
			free(cmd[i].command);
		if (cmd[i].path != NULL)
			free(cmd[i].path);
		if (cmd[i].args != NULL)
			free_double_pointer(cmd[i].args);
	}
	free(cmd);
	cmd = NULL;
}

/** Frees char ** variables
 */
void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

/** Frees t_mini mini, used when leaving minishell
 *maybe when signals exit the program
 */
void	free_mini(t_mini *mini)
{
	if (mini->envp)
	{
		free_double_pointer(mini->envp);
		mini->envp = NULL;
	}
	free_double_pointer(mini->builtins);
	mini->builtins = NULL;
	free_double_pointer(mini->paths);
	mini->paths = NULL;
}
