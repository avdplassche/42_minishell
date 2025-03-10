

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

	i = mini->cursor - 1;
	quote.dbl = 0;
	quote.sgl = 0;
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &quote);
		if (contain_char(charset, mini->line[i]))
			if (!quote.sgl && !quote.dbl)
				return (i);
	}
	return (i);
}

char	*get_cmd_bin(t_mini *mini)
{
	char	*temp;
	int		len;
	int		i;
	char	*dest;

	len = get_last_index(mini);
	temp = ft_substr(mini->line, mini->cursor, len - mini->cursor);
	while (contain_char(SPACE_SET, mini->line[len]))
		len++;
	mini->cursor = len;
	i = need_dollar_substitution(temp);
	while (i > -1)
	{
		temp = translate_dollar_sign(mini, temp, i);
		i = need_dollar_substitution(temp);
	}
	if (!contain_quotes(temp))
		dest = ft_strdup(temp);
	else
		dest = clean_command_quotes(temp);
	if (contain_char("<>|", mini->line[mini->cursor]))
		mini->cursor++;
	while (mini->line[mini->cursor] == ' ')
		mini->cursor++;
	return (free(temp), dest);

}

