
#include "minishell.h"

/*static void	modify_envp_array(t_mini *mini, t_cmd *cmd)
{
	
	//int	i;
	int	len;

	(void)cmd;
	len = string_array_len(mini->envp);
	DEBUG("the len of the string %d before the string array push\n", len);
	mini->envp = string_array_push(mini->envp);
	if (!mini->envp)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	len = string_array_len(mini->envp);
	DEBUG("the len of the string %d before the string array push\n", len);
	//i++;	//when calling the funvtion to make it bigger, you need to null check the result, and free it if necesary
	//set the mini ;ast return to the right value
	return ;
}*/

static int	is_already_in_envp(t_mini *mini, t_cmd *cmd)
{
	int i;

	i = 0;
	while (mini->envp[i])
	{
		DEBUG("entered the is already in envp function\n");
		if (string_array_find_string(mini->envp, cmd->args[i]) != NULL)
		{
			mini->last_return = CMD_NOT_FOUND;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	is_leading_int(t_mini *mini, t_cmd *cmd)
{
	int	i;
	
	i = 1;
	while (i <= cmd->arg_amount)
	{
		if (ft_isdigit(cmd->args[i][0]))
		{
			print_error("Minishell: '%s': not a valid identifier\n", cmd->args[i], 2);
			mini->last_return = CMD_NOT_FOUND;
			return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	if (cmd->arg_amount == 0)
	{
		sort_array(mini->envp, string_array_len(mini->envp));
		string_array_print(mini->envp);
	}
	if (cmd->arg_amount > 0)
	{
		if (is_leading_int(mini, cmd))
		{
			return (mini->last_return);
		}
		if (mini->envp && is_already_in_envp(mini, cmd))
		{
			return (mini->last_return);
		}
		/*else
		{
			modify_envp_array(mini, cmd);
		}*/
	}
	return (mini->last_return);
}
