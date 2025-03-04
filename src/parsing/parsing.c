
#include "../../includes/minishell.h"

/** Initialize command tokens
 * @param mini t_mini containing the amount of comands in the current line
 * @param cmd command structure
 * @param i index of the cmd structure
 *
 */
int	init_cmd(t_cmd *cmd, int i)   //change it in void ?
{
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->is_path = NULL;
	cmd->id = i + 1;
	cmd->type = -1;
	cmd->in_redir_total = 0;
	cmd->out_redir_total = 0;
	cmd->delimiter_total = 0;
	cmd->out_appredir_total = 0;
	return (0);
}

int	is_valid_command(t_mini *mini)
{
	if (!(is_valid_quote(mini)))
		return (printf("quote error\n\n-----------------------------------------------\n")
			, 0); //a revoir
	if (mini->line[0] == '|')
		return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
	return (1);
}


int	parsing(t_mini *mini, t_cmd *cmd)
{
	int		i;

	i = -1;
	mini->line = ft_strtrim(mini->line, SPACE_SET);
	if (!(is_valid_command(mini)))
	{
		mini->last_return = 127;
		return (-1);
	}
	if (mini->cmd_amount > 1)
		cmd = (t_cmd *)malloc(sizeof(t_cmd) * mini->cmd_amount);
			//malloc protection
	while (++i < mini->cmd_amount)
	{
		init_cmd(&cmd[i], i);
		fill_cmd_structure(mini, &cmd[i]);
	}
	if (DEBUGG_PARSING == 1)
		debug_parsing(mini, cmd);
	return (0);
}


