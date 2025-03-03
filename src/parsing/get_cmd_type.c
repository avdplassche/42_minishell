
#include "../../includes/minishell.h"

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
	while (++i < BUILTIN_AMOUNT)
	{
		if (!(ft_strncmp(mini->builtins[i], cmd->command, len)))
		{
			cmd->type = BUILTIN;
			return (0);
		}
	}

	/* NOT FINISHED*/

	cmd->type = UNVALID;
	return (0);
}
