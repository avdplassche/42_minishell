
#include "minishell.h"

int	builtin_cd(t_mini *mini, t_cmd *cmd)
{
	char	*path;

	if (cmd->arg_amount == 0 || cmd->args[1] == NULL)
	{
		path = ft_get_env(mini, "HOME");
		if (!path)
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			mini->last_return = CMD_NOT_FOUND;
			return (mini->last_return);
		}
	}
	else if (cmd->arg_amount > 1)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
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
		print_error("Minishell: cd: %s: No such file or directory\n", path);
		mini->last_return = CMD_NOT_FOUND;
	}
	return (mini->last_return);
}
