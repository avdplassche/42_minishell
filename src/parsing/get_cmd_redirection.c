
#include "minishell.h"

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

int	init_redirections(t_mini *mini, t_cmd *cmd)
{
	int	j;

	j = 0;
	cmd->heredoc_amount = 0;
	cmd->redir_amount = count_redirections(mini, mini->cursor);
	if (!cmd->redir_amount)
		return (0);
	cmd->redir = malloc(sizeof(t_redir) * (cmd->redir_amount));
	if (!cmd->redir)
		return (-1);
	while (is_angle_bracket(mini->line[mini->cursor]))
		get_cmd_redirection(mini, cmd, j++);
	return (j);
}

int	get_cmd_redir_type(t_mini *mini)
{
	if (mini->line[mini->cursor] == '<')
	{
		if (mini->line[++mini->cursor] == '<')
			return (mini->cursor++, HERE_DOC);
		else
			return (IN_REDIR);
	}
	else if (mini->line[mini->cursor] == '>')
	{
		if (mini->line[++mini->cursor] == '>')
			return (mini->cursor++, OUT_APPEND);
		else
			return (OUT_REDIR);
	}
	return (0);
}

int	get_cmd_redirection(t_mini *mini, t_cmd *cmd, int j)
{
	int	sign;

	sign = get_cmd_redir_type(mini);
	while (contain_char(SPACES, mini->line[mini->cursor]))
		mini->cursor++;
	cmd->redir[j].pathname = get_cmd_bin(mini);
	cmd->redir[j].type = sign;
	if (cmd->redir[j].type == HERE_DOC)
		cmd->heredoc_amount++;
	return (0);
}
