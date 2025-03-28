
#include "minishell.h"

void	wait_for_chilren(t_mini *mini, t_cmd *cmd)
{
	int	status;
	int	i;

	i = 0;
	while (i < mini->cmd_count)\
	{
		waitpid(cmd[i++].pid, &status, 0);
	}
}