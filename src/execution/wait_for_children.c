
#include "minishell.h"

void	wait_for_chilren(t_mini *mini, t_cmd *cmd_array)
{
	int	status;
	int	i;

	i = 0;
	while (i < mini->cmd_count)
	{
		waitpid(cmd_array[i++].pid, &status, 0);
	}
}