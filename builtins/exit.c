

#include "minishell.h"


//exit with no options
int	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	if (cmd->args && cmd->args[2])
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", STDOUT_FILENO);
		mini->last_return = 1;
		return (1);
	}
	if (cmd->args && cmd->args[1])
	{
		if (is_valid_arithmetic_exit(cmd->args[1]))
		{
			mini->last_return = ft_atoi(cmd->args[1]) & 255; //double check this
		}
		else
		{
			print_error("minishell: exit: %s : numeric argument required\n", cmd->args[1], 1);
			mini->last_return = 255;
		}
	}
	else
	{
		mini->last_return = 0; // in the case whhere its exit 0
	}
	if (mini->fd_backup->stdin_backup != -1 || mini->fd_backup->stdout_backup != -1)
		restore_standard_fd(mini);
	mini->should_exit = true;
	exit_minishell(mini, cmd);
	return mini->last_return;
}


//teminates the current shell session
// returns an exit status code 
// 0 is success, non zero indicate errors.
//make the last return go all the way back up to main and handle in main