
#include "minishell.h"

static int	is_leading_int(t_mini *mini, t_cmd *cmd)
{
	int	i;
	
	i = 0;
	while (i < cmd->arg_amount)
	{
		if (ft_isdigit(cmd->args[i + 1][0]))
		{
			print_error("Minishell: '%s': not a valid identifier\n", cmd->args[i + 1], 2);
			mini->last_return = CMD_NOT_FOUND;
			return (1);
		}
		i++;
	}
	return (0);
}
//export with no options
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
			exit_minishell(mini, cmd);
		}

	}
	return (mini->last_return);
}
//cases to be careful with
// minishell: export: '123hello' : not a valid identifier
// export _123hello --> works with the underscore at the beginign 
// add the prefix declare -x in front of all the enironment variables
// contrarily to the env command, this lists them in alphabetical order 

// export output when just writing export 
/// _123hello='' // if there is no path, need to replace with single quotes to signal it is to do
//  test=hello

// scenario of two different arguments inside export 
// separated and each will have its own environ,entarea 
// for example 
// export hello world

//ascii order of the variables so lower case goes at the end

//use ft_setenv 

// add the quotes to the path 


//export var += VALUE (concatnene values)