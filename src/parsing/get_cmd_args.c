#include "../../includes/minishell.h"


int	get_arg_amount(t_mini *mini)
{
	int		i;
	t_quote	quote;
	int		count;
	char	charset[4] = "|<>";

	i = mini->cursor - 1;
	quote.sgl = 0;
	quote.dbl = 0;
	count = 1;
	while (mini->line[++i] && !(contain_char(charset, mini->line[i])))
	{
		quote_enclosure_handle(mini->line[i], &quote);
		if (mini->line[i] == ' ' && !quote.sgl && !quote.dbl)
		{
			while (mini->line[i] == ' ')
				i++;
			if (!(contain_char(charset, mini->line[i])))
				count++;
			else
				break ;
		}
	}
	return (count);
}

/** Fill cmd arg tokens, a char** that will be used in execve
 * @param cmd_line the command line from the prompt
 * @param cmd_struct the command structure to fill
 * @return error ? not set yet
 */
int	get_cmd_args(t_mini *mini, t_cmd *cmd)
{
	int		i;

	i = 0;
	cmd->arg_amount = get_arg_amount(mini);
	cmd->args = (char **)malloc(sizeof(char *) * (cmd->arg_amount + 2));
	cmd->args[i] = ft_strdup(cmd->command);
	while (++i <= cmd->arg_amount)
		cmd->args[i] = get_cmd_bin(mini);
	cmd->args[i] = NULL;
	return (0);
}
