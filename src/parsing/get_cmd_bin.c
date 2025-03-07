

#include "../../includes/minishell.h"


/** Get the command's last index, use it to substring
 * @param mini t_mini structure, containing current line to work with
 * @return i : last index of the command
*/
int	get_last_index(t_mini *mini)
{
	int		i;
	t_quote	quote;
	char	charset[5] = " <>|";

	i = 0;
	quote.dbl = 0;
	quote.sgl = 0;
	while (mini->line[i])
	{
		if (contain_char(charset, mini->line[i]))
			if (!quote.sgl && !quote.dbl && i)
				return (i);
		quote_enclosure_handle(mini->line[i], &quote);
		i++;
	}
	return (i);
}

int	get_cmd_bin(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*temp;
	int		len;

	i = mini->cursor;
	len = get_last_index(mini);
	temp = ft_substr(mini->line, i, len);   //replace i by cursor ?
	while (contain_char(SPACE_SET, mini->line[len]))
		len++;
	mini->cursor = len;
	printf("Substring before $ substitution : %s$\n\n", temp);
	while (need_dollar_substitution(temp) != -1)
	{
		printf("Need Substitution at : %d\n\n", need_dollar_substitution(temp)),
		temp = translate_dollar_sign(mini, temp, need_dollar_substitution(temp)); //is there quotes in env ?
		// printf("temp : %s\n\n", temp);
	}
	if (!contain_quotes(temp))
		cmd->command = ft_strdup(temp);
	else
		clean_command_quotes(cmd, temp);
	return (free(temp), 0);
}

