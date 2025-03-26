
#include "minishell.h"

void	execute_pipe(t_mini *mini, t_cmd *cmd)
{
	int	i;
	t_pipefds *p;

	i = 0;
	p = mini->pipes;
	while (i < mini->cmd_count - 1)
	{
		pipe(p->fildes);
		cmd[i].pipe_out = p;
		cmd[i + 1].pipe_in = p;
		execute_command(cmd + i);
		p++;
		i++;
	}
	execute_command(cmd + i);
}