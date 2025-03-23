
#include "minishell.h"

int	builtin_cd(t_cmd *cmd, t_mini *mini)
{
	char	*path;
	int		status;

	path = cmd->args[1];
	if (path == NULL)
	{
		path = ft_get_env(mini, "HOME");
		if (path == NULL)
		{
			printf("Minishell: cd: HOME not set\n");
			mini->last_return = CMD_NOT_FOUND;
			return (mini->last_return);
		}
	}
	if (string_array_len(cmd->args) > 2)
	{
		printf("Minishell: cd: too many arguments\n");
		mini->last_return = CMD_NOT_FOUND;
		return (mini->last_return);
	}
	if (chdir(path) == 0)
	{
		DEBUG("entered the chdir path function\n");
		status = update_old_pwd_env(mini);
		if (status != 0)
			return (mini->last_return);
		status = update_pwd_env(mini, "PWD");
		if (status != 0)
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
