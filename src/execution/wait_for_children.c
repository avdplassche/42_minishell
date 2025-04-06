
#include "minishell.h"

void	wait_for_children(t_mini *mini, t_cmd *cmd)
{
	int	wait_status;
	//int status;
	int	i;

	i = 0;
	while (i < mini->cmd_count)
	{
		waitpid(cmd[i].pid, &wait_status, 0);
		i++;
	}
	//status = WEXITSTATUS(wait_status);
}
