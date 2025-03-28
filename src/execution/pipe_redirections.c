
#include "minishell.h"

void	redirect_command_input(t_mini *mini, t_cmd *cmd)
{
	if (!cmd->pipe_in)
	{
		if (!(cmd->type == HERE_DOC) && cmd == &cmd[0])
		{
			if (mini->fd_in < 0)
				minishell_exit(mini, cmd);
			dup_fd(mini, cmd, mini->fd_in, STDIN_FILENO);
		}
	}
	else
	{
		close_fd(mini, cmd, mini->fd_in);
		if (cmd->pipe_in)
			close_fd(mini, cmd, cmd->pipe_in->write);
		dup_fd(mini, cmd, cmd->pipe_in->read, STDIN_FILENO);
	}
}

void	redirect_command_output(t_mini *mini, t_cmd *cmd)
{
	if (!cmd->pipe_out)
	{
		if (mini->fd_out < 0)
			minishell_exit(mini, cmd);
		dup_fd(mini, cmd, mini->fd_out, STDOUT_FILENO);
	}
	else
	{
		close_fd(mini, cmd, mini->fd_out);
		close_fd(mini, cmd, cmd->pipe_out->read);
		dup_fd(mini, cmd, cmd->pipe_out->read, STDOUT_FILENO);
	}
}