

#include "../../includes/minishell.h"




/** Fill command structure (for 1 command of the command line)
 * @param mini t_mini structure, containing current line to work with
 * @param cmd_s an empty structure that the function will fill
 * @return not set yet, errors
*/
int	fill_cmd_structure(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->total_cmd)
	{
		get_cmd_string(mini, cmd);
		if (get_cmd_type(mini, cmd) == -1)  // error
			return (-1);
		if (mini->line[cmd->index])
			get_cmd_args(mini, cmd);
		else
			return (0);
		// get_cmd_filename(cmd);
		// fill_cmd_booleans(cmd_struct);
	}
	return (0);
}
