

#include "../../includes/minishell.h"

/**Count the amount of redirections in order
 * to malloc t_file structures for each redir
 */
int	count_redirections(t_mini *mini)
{
	int		count;
	int		i;
	t_quote	q;

	q.sgl = 0;
	q.dbl = 0;
	i = mini->cursor - 1;
	count = 0;
	while (mini->line[++i] && mini->line[i] != '|' && !q.sgl && !q.dbl)
	{
		quote_enclosure_handle(mini->line[i], &q);
		if (mini->line[i] == '<' && !q.sgl && !q.dbl)
		{
			count++;
			if (mini->line[i + 1] == '<')
				i++;
		}
		if (mini->line[i] == '>' && !q.sgl && !q.dbl)
		{
			count++;
			if (mini->line[i + 1] == '>')
				i++;
		}
	}
	return (count);
}

/** Fill command structure (for 1 command of the command line)
 * @param mini t_mini structure, containing current line to work with
 * @param cmd an empty structure that the function will fill
 * @return not set yet, errors
*/
int	fill_cmd_structure(t_mini *mini, t_cmd *cmd)
{

	cmd->redir_amount = count_redirections(mini);

	cmd->file = malloc(sizeof(t_file) * (cmd->redir_amount));
	cmd->command = get_cmd_bin(mini);

	if (mini->line[mini->cursor])
		get_cmd_args(mini, cmd);

	cmd->type = get_cmd_type(mini, cmd);
	if (cmd->type == -1)
		return (-1);


	else if (mini->line[mini->cursor] == '|')
	{
		mini->cursor++;
		while (mini->line[mini->cursor] == ' ')
			mini->cursor++;
	}

	return (0);
}
