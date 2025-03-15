

#include "../../includes/minishell.h"


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

/**Count the amount of redirections in order
 * to malloc t_file structures for each redir
 */
int	count_redirections(t_mini *mini, int i)
{
	int		count;
	t_quote	q;

	q.sgl = 0;
	q.dbl = 0;
	count = 0;
	while (mini->line[i] && mini->line[i] != '|')
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
		i++;
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
	int	i;
	int	j;

	j = 0;
	i = 0;
	cmd->redir_amount = count_redirections(mini, mini->cursor);
	if (cmd->redir_amount)
	{
		// init_redirections(mini, cmd);
		cmd->redir = malloc(sizeof(t_redir) * (cmd->redir_amount));
		if (!cmd->redir)
			return (MALLOC_ERR);
		while (is_angle_bracket(mini->line[mini->cursor]))
			get_cmd_redirection(mini, cmd, j++);
	}
	cmd->command = get_cmd_bin(mini);
	if (mini->line[mini->cursor])
		cmd->arg_amount = count_arguments(mini);
	if (cmd->arg_amount)
	{
		cmd->args = (char **)malloc(sizeof(char *) * (cmd->arg_amount + 2));
		if (!cmd->args)
			return (MALLOC_ERR);
		cmd->args[i++] = ft_strdup(cmd->command);
	}
	while (mini->line[mini->cursor] && mini->line[mini->cursor] != '|'
		&& (cmd->arg_amount || cmd->redir_amount))
	{
		if (is_angle_bracket(mini->line[mini->cursor]) && cmd->redir_amount)
			get_cmd_redirection(mini, cmd, j++);
		else if (cmd->arg_amount)
			get_cmd_args(mini, cmd, i++);
	}
	if (cmd->arg_amount)
		cmd->args[i] = NULL;
	cmd->type = get_cmd_type(mini, cmd);
	if (cmd->type == -1)
		return (-1);
	if (mini->line[mini->cursor] == '|')
	{
		mini->cursor++;
		while (mini->line[mini->cursor] && mini->line[mini->cursor] == ' ')
			mini->cursor++;
	}
	return (0);
}
