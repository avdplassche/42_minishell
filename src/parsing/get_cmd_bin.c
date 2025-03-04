

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

	printf("cursor :%d\n", mini->cursor);
	i = mini->cursor;
	len = get_last_index(mini);
	temp = ft_substr(mini->line, i, len);   //replace i by cursor ?
	while (contain_char(SPACE_SET, mini->line[len]))
		len++;
	mini->cursor = len;
	printf("Substring before cleaning quotes : %s$\n\n", temp);
	if (need_sigil_sub(temp))
	{
		printf("Need $ translation\n\n");
		translate_sigil_sign(mini, temp); //is there quotes in env ?
	}
	if (!contain_quotes(temp))
	{
		cmd->command = ft_strdup(temp);
		return (free(temp), 0);
	}
	clean_command_quotes(cmd, temp);
	return (free(temp), 0);
}

