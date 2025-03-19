
#include "minishell.h"

//cd with only a relative or absolute pat

int	builtin_cd(t_cmd *cmd, t_mini *mini)
{
	char	*path;

	path = cmd->args[1];
	if (path == NULL)
	{
		perror("path is invalid\n");
		return (-1);
	}
	if (string_array_len(cmd->args) > 2)
	{
		printf("Minishell: cd: too many arguments\n");
		return (-1);
	}
	if (chdir(path) == 0)
	{
		//change the enrionment variable 
		builtin_pwd(cmd, mini);
		mini->last_return = 0;
	}
	else
	{
		printf("Minishell: cd: %s: No such file in directory\n", path);
		mini->last_return = CMD_NOT_FOUND;
	}
	return (mini->last_return);
}
