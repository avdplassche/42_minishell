
#include "minishell.h"

/** Check if cmd is echo -n
 * @return -  1 if echo -n (so type is builtin)
 * @return - 0 if echo with other args(so type is user command)
 */
int	is_builtin_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	if (!cmd->arg_amount)
		return (1);
	j = 0;
	while (cmd->args[++j])
	{
		i = 0;
		if (cmd->args[j][i] == '-')
		{
			while (cmd->args[j][++i])
			{
				if (cmd->args[j][i] != 'n' && j == 1)
					return (0);
				else if (cmd->args[j][i] != 'n' && j > 1)
					break ;
			}
		}
		// j++;
	}
	printf("%d\n", j - 1);
	cmd->echo_n_index = j - 1;
	return (1);
}

int	is_user_command(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = -1;
	while (mini->paths[++i])
	{
		temp = ft_strjoin(mini->paths[i], "/");
		cmd->path = ft_strjoin(temp, cmd->command);
		if (access(cmd->path, F_OK) == 0 && access(cmd->path, X_OK) == 0)
			return (free(temp), 1);
		free(temp);
		temp = NULL;
		free(cmd->path);
		cmd->path = NULL;
	}
	return (0);
}


/** Fill cmd type token
 * @param mini t_mini structure, containing current line to work with
 * @param cmd cmd struct
 * @return - 0 (BIN) the command can be found in PATH
 * @return - 1 (BUILTIN) the command can be found in the 'builtins' dir
 * @return - -1 (UNVALID) the command is not valid
*/
int	get_cmd_type(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(cmd->command);
	if (!(ft_strncmp(cmd->command, "echo", len)))
	{
		if (is_builtin_echo(cmd))
			return (BUILTIN);
		else
			return (is_user_command(mini, cmd), USER);
	}
	while (++i < BUILTIN_AMOUNT)
	{
		if (!(ft_strncmp(mini->builtins[i], cmd->command, len)))
			return (BUILTIN);
	}
	if (is_user_command(mini, cmd))
		return (USER);
	return (UNVALID);
}
