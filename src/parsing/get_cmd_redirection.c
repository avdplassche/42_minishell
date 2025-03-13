

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
	else
	{
		if (mini->line[++mini->cursor] == '>')
		{
			mini->cursor++;
			return (OUT_APPEND);
		}
		else
			return (OUT_REDIR);
	}
}

int	get_cmd_redirection(t_mini *mini, t_cmd *cmd, int index)
{
	// int	i;

	cmd->file[index].type = get_cmd_redir_type(mini);
	// i = mini->cursor;
	cmd->file[index].path_name = get_cmd_bin(mini);
	// (void)mini;
	// (void)cmd;
	// int	i;

	// i = -1;


	return (0);
}

