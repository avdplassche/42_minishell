

#include "minishell.h"



/** Fill command structure (for 1 command of the command line)
 * @param mini t_mini structure, containing current line to work with
 * @param cmd an empty structure that the function will fill
 * @return not set yet, errors
*/
int	fill_cmd_structure(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	j;

	mini->line = dollar_handle(mini, mini->line);
	mini->line = wildcard_handle(mini->line);
	i = 0;
	j = init_redirections(mini, cmd);
	if (j < 0)
		return (MALLOC_ERROR);
	cmd->command = get_cmd_bin(mini);
	if (mini->line[mini->cursor])
		i = init_arguments(mini, cmd);
	if (i < 0)
		return (MALLOC_ERROR);
	while (mini->line[mini->cursor] && mini->line[mini->cursor] != '|')
	{
		if (is_angle_bracket(mini->line[mini->cursor]) && cmd->redir_amount)
			get_cmd_redirection(mini, cmd, j++);
		else if (cmd->arg_amount)
			get_cmd_args(mini, cmd, i++);
	}
	if (cmd->arg_amount)
		cmd->args[i] = NULL;
	cmd->type = get_cmd_type(mini, cmd);
	if (cmd->type == -1)
		return (-1);
	return (0);
}
