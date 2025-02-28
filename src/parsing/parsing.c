
#include "../../includes/minishell.h"

/** Count command amount in command line, that will be used for pipes.
 * @param mini t_mini containing the command line
 * @return number of commands
 * @note proceed by countint pipe char '|'
 */
int	count_cmd(t_mini *mini)
{
	int	i;
	int	count;

	count = 1;
	i = -1;
	while (mini->line[++i])
		if (mini->line[i] == '|')
			count++;
	return (count);
}

/** Initialize command tokens
 * @param mini t_mini containing the amount of comands in the current line
 * @param cmd command structure
 * @param i index of the cmd structure
 *
 */
int	init_cmd(t_mini *mini, t_cmd *cmd, int i)
{
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->is_path = NULL;
	cmd->total_cmd = count_cmd(mini);
	cmd->id = i + 1;
	cmd->type = -1;
	cmd->in_redir_amount = 0;
	cmd->out_redir_amount = 0;
	cmd->delimiter_amount = 0;
	cmd->out_appredir_amount = 0;
	cmd->index = 0;
	return (0);
}




int	parsing(t_mini *mini, t_cmd *cmd)
{
	int		cmd_total;
	int		i;

	i = -1;
	mini->line = ft_strtrim(mini->line, " 	\n");

	if (mini->line[0] == '$')
	{
		if (handle_dollar_sign(mini, cmd) == -1)
		{
			mini->last_return = 127;
			return (-1);
		}
	}

	/* * * * * Those conditions might go to a check_cmd_validity function * * * */

	if (!(is_valid_quote(mini)) || !(even_quote(mini)))
		return (printf("quote error\n-----------------------------------------------\n"), -1); //a revoir
	if (mini->line[0] == '|')
		return (printf("minishell: syntax error near unexpected token `|'\n"), -1);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

	cmd_total = count_cmd(mini);
	if (cmd_total > 1)
		cmd = (t_cmd *)malloc(sizeof(t_cmd) * cmd_total);
			//malloc protection
	while (++i < cmd_total)
	{
		init_cmd(mini, &cmd[i], i);
		fill_cmd_structure(mini, cmd);
	}
	if (DEBUGG_PARSING == 1)
		debug_parsing(mini, cmd);
	return (0);
}


