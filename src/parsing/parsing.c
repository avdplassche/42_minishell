
#include "../../includes/minishell.h"

/** Initialize command tokens
 * @param mini t_mini containing the amount of comands in the current line
 * @param cmd command structure
 * @param i index of the cmd structure
 *
 */
void	init_cmd(t_cmd *cmd, int i)   //change it to void ?
{
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->filename = NULL;
	cmd->id = i + 1;
	cmd->type = -1;
	cmd->pipe = 0;
	cmd->in_redir_total = 0;
	cmd->out_redir_total = 0;
	cmd->in_delimiter_total = 0;
	cmd->out_appredir_total = 0;
}

int	is_valid_command(t_mini *mini)
{
	if (!(is_valid_quote(mini)))
		return (printf("quote error\n\n-----------------------------------------------\n")
			, 0); //maybe checking valid quote is a bit obsolete ?
	if (mini->line[0] == '|')
		return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
	return (1);
}

int	set_return_value(t_mini *mini, int value)
{
	mini->last_return = value;
	if (value == 127)  //when to return (1) ?
		return (-1);
	return (0);
}

int	parsing(t_mini *mini, t_cmd *cmd)
{
	int		i;

	i = -1;
	if (!(is_valid_command(mini)))
		return (set_return_value(mini, 127));
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * mini->cmd_amount);
	if (!cmd)//malloc protection
		return (-1);
	while (++i < mini->cmd_amount)
	{
		init_cmd(&cmd[i], i);
		fill_cmd_structure(mini, &cmd[i]);
	}
	if (DEBUGG_PARSING == 1)
		debug_parsing_print(mini, cmd);
	return (0);
}


