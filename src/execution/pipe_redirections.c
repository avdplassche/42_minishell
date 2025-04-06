
#include "minishell.h"

void	parent_closes_all_pipes(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count - 1)
	{
		close(mini->pipes[i].read);
		close(mini->pipes[i].write);
		i++;
	}
	free(mini->pipes);
	mini->pipes = NULL;
}

void	connect_command_pipeline(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	int	i;

	if (cmd_index > 0)
	{
		dup2_fd(mini, cmd, mini->pipes[cmd_index - 1].read, STDIN_FILENO);
	}
	if (cmd_index < mini->cmd_count - 1)
	{
		dup2_fd(mini, cmd, mini->pipes[cmd_index].write, STDOUT_FILENO);
	}
	i = 0;
	while (i < mini->cmd_count - 1)
	{
		close(mini->pipes[i].read);
		close(mini->pipes[i].write);
		i++;
	}
}
