
#include "minishell.h"

void	redirect_command_input(t_mini *mini, t_cmd *cmd)
{
	if (cmd && cmd->pipe_in)
	{
		close_fd(mini, cmd, cmd->pipe_in->write);
		dup_fd(mini, cmd, cmd->pipe_in->read, STDIN_FILENO);
	}
}

void	redirect_command_output(t_mini *mini, t_cmd *cmd)
{
	if (cmd && cmd->pipe_out)
	{
		close_fd(mini, cmd, cmd->pipe_out->read);
		dup_fd(mini, cmd, cmd->pipe_out->write, STDOUT_FILENO);
	}
}