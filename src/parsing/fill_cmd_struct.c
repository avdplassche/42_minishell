

#include "../../includes/minishell.h"

// int	is_redirected(t_cmd *cmd)
// {



// }

/** Fill command structure (for 1 command of the command line)
 * @param mini t_mini structure, containing current line to work with
 * @param cmd an empty structure that the function will fill
 * @return not set yet, errors
*/
int	fill_cmd_structure(t_mini *mini, t_cmd *cmd)
{
	// get_cmd_total_redir(mini, cmd);
	cmd->command = get_cmd_bin(mini);
	if (mini->line[mini->cursor] && mini->line[mini->cursor] != '>' && mini->line[mini->cursor] != '<')
		get_cmd_args(mini, cmd);
	cmd->type = get_cmd_type(mini, cmd);
	if (cmd->type == -1)
		return (-1); //unvalid
	printf("char :%c\n",  mini->line[mini->cursor]);
	
	if (contain_char("<>", mini->line[mini->cursor])) // maybe do a while and change tructure to char *outfilename
		get_cmd_redirection(mini, cmd);
	else if (mini->line[mini->cursor] == '|')
	{
		mini->cursor++;
		while (mini->line[mini->cursor] == ' ')
			mini->cursor++;
	}
	// get_cmd_filename(cmd);
	// mini->cursor =
	return (0);
}
