
#include "minishell.h"

int	builtin_cd(t_cmd *cmd, t_mini *mini)
{
	char	*path;
	//char	*old_pwd;

	//old_pwd = get_current_workdir(mini);
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
		update_pwd_env(mini, "PWD");
		//if (old_pwd)
		mini->last_return = 0;
	}
	else
	{
		printf("Minishell: cd: %s: No such file in directory\n", path);
		mini->last_return = CMD_NOT_FOUND;
	}
	//free(old_pwd);
	return (mini->last_return);
}
