

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
		quote_enclosure_handle(mini->line[i], &quote);
		if (contain_char(charset, mini->line[i]))
			if (!quote.sgl && !quote.dbl)
				return (i);
		i++;
	}
	return (i);
}

int	get_cmd_bin(t_mini *mini, t_cmd *cmd)
{
	char	*temp;
	int		len;
	int		i;

	len = get_last_index(mini);
	temp = ft_substr(mini->line, mini->cursor, len);
	while (contain_char(SPACE_SET, mini->line[len]))
		len++;
	mini->cursor = len;
	printf("Substring before $ substitution : %s$\n\n", temp);
	i = need_dollar_substitution(temp);
	while (i != -1)
	{
		printf("Need Substitution at : %d\n\n", i);
		temp = translate_dollar_sign(mini, temp, i); //is there quotes in env ?
		printf("cmd checkpoint : %s\n", temp);
		i = need_dollar_substitution(temp);
	}
	if (!contain_quotes(temp))
		cmd->command = ft_strdup(temp);
	else
		clean_command_quotes(cmd, temp);
	return (free(temp), 0);
}

