#include "../../includes/minishell.h"

int	get_arg_amount(t_mini *mini)
{
	int		i;
	t_quote	quote;
	int		count;

	i = mini->cursor - 1;
	quote.sgl = 0;
	quote.dbl = 0;
	count = 1;
	while (mini->line[++i] && !(contain_char("|<>", mini->line[i])))
	{
		quote_enclosure_handle(mini->line[i], &quote);
		// printf("line[%d] = %c sq = %d dq = %d\n", i, mini->line[i], quote.sgl, quote.dbl);
		if (mini->line[i] == ' ' && !quote.sgl && !quote.dbl)
		{
			printf("yes\n");
			// while (mini->line[i] == ' ' && (!quote.sgl) && (!quote.dbl))
			// 	i++;
			count++;
		}
	}
	return (count);
}

/** Fill cmd arg tokens, a char** that will be used in execve
 * @param cmd_line the command line from the prompt
 * @param cmd_struct the command structure to fill
 * @return error ? not set yet
 *
 */
int	get_cmd_args(t_mini *mini, t_cmd *cmd)
{
	int		i;
// 	int		j;
	int		k;
// 	char	*arg;

	i = 0;
	k = get_arg_amount(mini);
	cmd->args = (char **)malloc(sizeof(char *) * (k + 2));
	cmd->args[i] = ft_strdup(cmd->command);
	while (++i <= k)
	{
		cmd->args[i] = get_cmd_bin(mini);
	}
	cmd->args[i] = NULL;
	return (0);
}
