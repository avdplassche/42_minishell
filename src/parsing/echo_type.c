#include "minishell.h"

static int	check_arg_one(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[1][++i])
	{
		if (cmd->args[1][i] == ' ')
			break ;
		else if (cmd->args[1][i] != 'n')
			return (0);
	}
	return (i);
}

static int	check_other_args(t_cmd *cmd, int j)
{
	int	i;

	i = -1;
	if (cmd->args[j][++i] != '-')
	{
		cmd->echo_n_index = j;
		return (1);
	}
	while (cmd->args[j][++i])
	{
		if (cmd->args[j][i] != 'n')
		{
			cmd->echo_n_index = j;
			return (1);
		}
	}
	return (1);
}

/** Check if cmd is echo -n
 * @return - 1 if echo -n (so type is builtin)
 * @return - 0 if echo with other args(so type is user command)
 */
int	is_builtin_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	cmd->echo_n_index = 0;
	if (!cmd->arg_amount)
		return (1);
	j = 1;
	i = 0;
	if (cmd->args[1][i] == '-')
		i = check_arg_one(cmd);
	else
		return (1);
	if (!i)
		return (0);
	else if (cmd->args[1][1] == 'e')
		return (0);
	else
		return (1);
	while (cmd->args[++j])
		if (check_other_args(cmd, j) == 1)
			return (1);
	return (1);
}
