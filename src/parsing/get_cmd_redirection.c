

#include "../../includes/minishell.h"

int	get_cmd_redir_type(t_mini *mini)
{
	if (mini->line[mini->cursor] == '<')
	{
		if (mini->line[++mini->cursor] == '<')
		{
			mini->cursor++;
			return (HERE_DOC);
		}
		else
			return (IN_REDIR);
	}
	else if (mini->line[mini->cursor] == '>')
	{
		if (mini->line[++mini->cursor] == '>')
		{
			mini->cursor++;
			return (OUT_APPEND);
		}
		else
			return (OUT_REDIR);
	}
	return (0);
}

int	get_cmd_redirection(t_mini *mini, t_cmd *cmd, int j)
{
	int	sign;


	sign = get_cmd_redir_type(mini);
	if (sign != HERE_DOC)
		cmd->redir[j].eof = NULL;

	while (contain_char(SPACES, mini->line[mini->cursor]))
		mini->cursor++;
	cmd->redir[j].pathname = get_cmd_bin(mini);
	cmd->redir[j].type = sign;
	if (cmd->redir[j].type == HERE_DOC)
		cmd->redir[j].eof = get_cmd_bin(mini);
	return (0);
}

