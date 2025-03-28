
#include "minishell.h"

void	redirect_command_input(t_mini *mini, t_cmd *cmd)
{
	printf("the command id of the command %s is %d\n", cmd->command, cmd->id);
	if (!cmd->pipe_in)
	{
		printf("entered the condition if !cmd->pipein\n");
		if (cmd->id == 1)
		{
			printf("entered the confitioon of id being 0 meaning it is the first command\n");
			if (mini->fd_in >= 0)
				minishell_exit(mini, cmd);
			dup_fd(mini, cmd, mini->fd_in, STDIN_FILENO);
		}
	}
	else
	{
		if (mini->fd_in >= 0)
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
		if (mini->fd_out >= 0)
			minishell_exit(mini, cmd);
		dup_fd(mini, cmd, mini->fd_out, STDOUT_FILENO);
	}
	else
	{
		if (mini->fd_out >= 0)
			close_fd(mini, cmd, mini->fd_out);
		close_fd(mini, cmd, cmd->pipe_out->read);
		dup_fd(mini, cmd, cmd->pipe_out->write, STDOUT_FILENO);
	}
}