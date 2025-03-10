

#include "../../includes/minishell.h"





/** Fill command structure (for 1 command of the command line)
 * @param mini t_mini structure, containing current line to work with
 * @param cmd an empty structure that the function will fill
 * @return not set yet, errors
*/
int	fill_cmd_structure(t_mini *mini, t_cmd *cmd)
{
	// get_cmd_total_redir(mini, cmd);
	cmd->command = get_cmd_bin(mini);
	if (mini->line[mini->cursor])
		get_cmd_args(mini, cmd);
	else
		return (0);
	if (get_cmd_type(mini, cmd) == -1)  //need to also check with arg -> (echo -n is built, echo isn't)
		return (-1);
	// get_cmd_filename(cmd);
	// mini->cursor =
	return (0);
}
