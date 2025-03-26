
#include "minishell.h"

static void	dup_fd(t_command *cmd, int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
		pipex_exit(cmd->pipex, "Dup2 failed\n");
	close_fd(cmd, fd);
}

static void connect_pipe(t_mini *mini, t_cmd *cmd)
{
	if (!cmd->pipe_in)
	{
		dup_fd(mini, cmd, mini->fd_in, STDIN_FILENO);
	}
	else
	{
		close_fd(mini, cmd, mini->fd_in);
		close_fd(mini, cmd, cmd->pipe_in->write);
		dup_fd(mini, cmd, cmd->pipe_in->read, STDIN_FILENO);
		close(STDIN_FILENO);
	}
}

void	execute_command(t_mini *mini, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		minishell_exit(mini, cmd);
	if (cmd->pid != 0)
	{
		if (cmd->pipe_in)
		{
			close_fd(mini, cmd, cmd->pipe_in->read);
			close_fd(cmd, mini, cmd->pipe_in->write);
		}
	}
	connect_pipe(mini, cmd);
	if (execve(cmd->path, cmd->args, mini->envp) == -1)
	{
		perror("execve");
		minishell_exit(mini, cmd);
	}
}

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
