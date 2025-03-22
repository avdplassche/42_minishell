
#include "minishell.h"

//cd with only a relative or absolute pat

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
			return (1);
		}
	}
	if (string_array_len(cmd->args) > 2)
	{
		printf("Minishell: cd: too many arguments\n");
		//free(old_pwd);
		return (-1);
	}
	if (chdir(path) == 0)
	{
		update_pwd_env(mini, cmd, "PWD");
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
