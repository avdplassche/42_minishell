
#include "minishell.h"

int	builtin_cd(t_cmd *cmd, t_mini *mini)
{
	char	*path;

	if (cmd->arg_amount == 0 || cmd->args[1] == NULL)
	{
		path = ft_get_env(mini, "HOME");
		if (!path)
		{
			printf("Minishell: cd: HOME not set\n");
			mini->last_return = CMD_NOT_FOUND;
			return (mini->last_return);
		}
	}
	else if (cmd->arg_amount > 1)
	{
		printf("Minishell: cd: too many arguments\n");
		mini->last_return = CMD_NOT_FOUND;
		return (mini->last_return);
	}
	else
	{
		path = cmd->args[1];
	}
	if (chdir(path) == 0)
	{
		if (update_old_pwd_env(mini) != 0 || update_pwd_env(mini, "PWD") != 0)
			return (mini->last_return);
		mini->last_return = 0;
	}
	else
	{
		printf("Minishell: cd: %s: No such file in directory\n", path);
		mini->last_return = CMD_NOT_FOUND;
	}
	return (mini->last_return);
}
