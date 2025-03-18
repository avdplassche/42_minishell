#include "minishell.h"


int	go_to_next_arg(t_mini *mini, t_quote *q, int i)
{
	char	charset[5] = " <>|";

	while (is_angle_bracket(mini->line[i]))
		i++;
	while (contain_char(SPACES, mini->line[i]))
		i++;
	while (mini->line[i])
	{
		if (contain_char(charset, mini->line[i]) && !q->dbl && !q->sgl)
			break ;
		i++;
		quote_enclosure_handle(mini->line[i], q);
	}
	while (contain_char(SPACES, mini->line[i]))
		i++;
	return (i);
}

/**Count the amount of arguments in order to fill cmd->args
 */
int	count_arguments(t_mini *mini)
{
	int		count;
	int		i;
	t_quote	q;

	q.sgl = 0;
	q.dbl = 0;
	i = mini->cursor;
	count = 0;
	while (mini->line[i] && mini->line[i] != '|' && !q.sgl && !q.dbl)
	{
		quote_enclosure_handle(mini->line[i], &q);
		if (is_angle_bracket(mini->line[i]))
			i = go_to_next_arg(mini, &q, i);
		else if (mini->line[i])
		{
			count++;
			i = go_to_next_arg(mini, &q, i);
		}
	}
	return (count);
}

int	init_arguments(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->arg_amount = count_arguments(mini);
	if (cmd->arg_amount)
	{
		cmd->args = (char **)malloc(sizeof(char *) * (cmd->arg_amount + 2));
		if (!cmd->args)
			return (-1);
		cmd->args[i++] = ft_strdup(cmd->command);
	}
	return (i);
}


/** Fill cmd arg tokens, a char** that will be used in execve
 * @param cmd_line the command line from the prompt
 * @param cmd_struct the command structure to fill
 * @return error ? not set yet
 */
int	get_cmd_args(t_mini *mini, t_cmd *cmd, int index)
{
	// int		i;

	// i = 0;
	// cmd->arg_amount = get_arg_amount(mini);
	// cmd->args = (char **)malloc(sizeof(char *) * (cmd->arg_amount + 2));
	// cmd->args[i] = ft_strdup(cmd->command);
	// while (++i <= cmd->arg_amount)
	cmd->args[index] = get_cmd_bin(mini);
	// cmd->args[i] = NULL;
	return (0);
}
