#include "minishell.h"


static void	print_invalid_command(char *command)
{
	printf("%s: command not found\n", command);
}



/** Fill command structure (for 1 command of the command line)
 * @param mini t_mini structure, containing current line to work with
 * @param cmd an empty structure that the function will fill
 * @return not set yet, errors
*/
void	fill_cmd_structure(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = init_redirections(mini, cmd);
	cmd->command = get_cmd_bin(mini);
	i = init_arguments(mini, cmd);
	while (mini->line[mini->cursor] && mini->line[mini->cursor] != '|')
	{	
		if (is_angle_bracket(mini->line[mini->cursor]) && cmd->redir_amount)
			get_cmd_redirection(mini, cmd, j++);
		else if (cmd->arg_amount)
			cmd->args[i++] = get_cmd_bin(mini);
	}
	if (cmd->arg_amount)
		cmd->args[i] = NULL;
	cmd->type = get_cmd_type(mini, cmd);
	// if (cmd->type == -1)
	// 	return (print_invalid_command(cmd->command));
}
