
#include "minishell.h"

int	builtin_env(t_mini *mini, t_cmd *cmd)
{
	(void)cmd;

	if (cmd->arg_amount >= 1)
	{
		perror("Minishell: env: too many arguments\n");
		mini->last_return = CMD_NOT_FOUND;
		return (-1);
	}
	string_array_print(mini->envp);
	return (0);
}
