

#include "../../includes/minishell.h"





/** Fill the command token, stops when it finds a redir, a pipe or a space
 * @param mini t_mini structure, containing current line to work with
 * @param cmd cmd struct
 *@return not set yet (maybe error)
*/
int	get_cmd_string(t_mini *mini, t_cmd *cmd)
{
	int		i;
	int		j;
	bool	double_quote;

	double_quote = 0;
	i = 0;
	j = 0;
	while (is_space(mini->line[i]) || is_quote(mini->line[i]))
	{
		if (mini->line[i] == 34)
		{
			if (double_quote == 0)
				double_quote = 1;
			else
				double_quote = 0;
		}
		i++;
	}
	if (double_quote == 0)
	{
		while (mini->line[i] && !(is_space(mini->line[i]))
			&& !(contain_char("<>|", mini->line[i]))
			&& !(is_quote(mini->line[i])))
		{
			i++;
			j++;
		}
	}
	else
	{
		while (mini->line[i] != '"')
		{
			i++;
			j++;
		}
	}
	cmd->command = ft_substr(mini->line, i - j, j);
	cmd->index = i;
	return (0);
}
