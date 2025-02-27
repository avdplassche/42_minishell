
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
	cmd->in_redir = 0;
	cmd->out_redir = 0;
	cmd->delimiter = 0;
	cmd->out_appredir = 0;
	cmd->index = 0;
	return (0);
}



/** Count number of quotes in command line
 * @param mini t_mini containing the command line
 * @return number of quotes in command line
 * @note 34 = '
 * @note 39 = "
 */
int	is_valid_quote(t_mini *mini)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (mini->line[++i])
	{
		if (is_quote(mini->line[i]))
			count++;
	}
	if (count % 2 == 1)
		return (0);
	else
	{
		while (!(is_quote(mini->line[i])))
			i--;
		count = mini->line[i];
		i--;
		while (!(is_quote(mini->line[i])))
			i--;
		if (count != mini->line[i] && count == 39)
			return (0);
	}
	return (1);

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

	/* * * * * Those conditions might go to a check_cmd function * * * */

	if (is_valid_quote(mini) == 0)
		return (printf("quote error\n-----------------------------------------------\n"), -1); //a revoir
	if (mini->line[0] == '|')
		return (printf("minishell: syntax error near unexpected token `|'\n"), -1);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


	if (!(contain_char(mini->line, ' ')))
	{

	}

	cmd_total = count_cmd(mini);
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


