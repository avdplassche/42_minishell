

#include "../../includes/minishell.h"


/** Get the command's last index, use it to substring
 * @param mini t_mini structure, containing current line to work with
 * @return i : last index of the command
*/
int	get_last_index(t_mini *mini)
{
	int		i;
	t_quote	quote;
	char	charset[4] = " <>|";

	i = 0;
	quote.dbl = 0;
	quote.sgl = 0;
	while (mini->line[i])
	{
		if (contain_char(charset, mini->line[i]))
			if (!quote.sgl && !quote.dbl && i)
				return (printf("i=%d\n",i), i);
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
	int		dollar_amount;

	i = mini->cursor;
	len = get_last_index(mini);
	temp = ft_substr(mini->line, i, len);   //replace i by cursor ?
	while (contain_char(SPACE_SET, mini->line[len]))
		len++;
	mini->cursor = len;
	printf("Substring before cleaning quotes : %s$\n\n", temp);
	dollar_amount = dollar_sub_needed(temp);
	printf("Need %d translation(s)\n\n", dollar_amount);
	while (dollar_sub_needed(temp)) //maybe calculate how many $signs are to be replaced
	{
		temp = translate_dollar_sign(mini, temp); //is there quotes in env ?
			//if (!temp)
	}
	printf("Substring after $ substitution : %s$\n\n", temp);
	if (!contain_quotes(temp))
		cmd->command = ft_strdup(temp);
	else
		clean_command_quotes(cmd, temp);
	printf("Substring after cleaning quotes : %s$\n\n", temp);
	return (free(temp), 0);
}

