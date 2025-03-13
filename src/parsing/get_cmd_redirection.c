

#include "../../includes/minishell.h"

int	get_cmd_redir_type(t_mini *mini)
{
	printf("cursor = %d\n", mini->cursor);
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
	printf("Index = %d\n", index);

	cmd->file[index].type = get_cmd_redir_type(mini);
	printf("Type= %d\n", cmd->file[index].type);
	cmd->file[index].path_name = get_cmd_bin(mini);


	return (0);
}

