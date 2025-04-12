
#include "minishell.h"

static void	modify_envp_array(t_mini *mini, t_cmd *cmd)
{
	char	**temp_env;

	temp_env = string_array_push(mini->envp, ft_strdup(cmd->args[1]));
	if (!temp_env)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	free(mini->envp);
	mini->envp = temp_env;
	return ;
}

static int	is_already_in_envp(t_mini *mini, t_cmd *cmd)
{
	int i;
	int	j;

	i = 0;
	j = 1;
	while (mini->envp[i] && j <= cmd->arg_amount)
	{
		DEBUG("entered the is already in envp function\n");
		if (string_array_find_string(mini->envp, cmd->args[j]) != NULL)
		{
			mini->last_return = CMD_NOT_FOUND;
			return (1);
		}
		i++;
		j++;
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
		sort_ascii_array(mini->envp, string_array_len(mini->envp));
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
		else
		{
			modify_envp_array(mini, cmd);
			sort_ascii_array(mini->envp, string_array_len(mini->envp));
			string_array_print(mini->envp);
		}
	}

	return (mini->last_return);
}
