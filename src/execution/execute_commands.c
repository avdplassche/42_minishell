
#include "minishell.h"

static void	redirect_pipes(t_mini *mini, t_cmd *cmd)
{
	redirect_command_input(mini, cmd);
	redirect_command_output(mini, cmd);
}

static void	execute_command(t_mini *mini, t_cmd *cmd)
{
	cmd->pid = fork(); // parent process forks a child 
	if (cmd->pid == -1)
		minishell_exit(mini, cmd);
	if (cmd->pid == 0)
	{
		printf("i am inside the child\n");
		printf("the path is %s\n", cmd->path);
		redirect_pipes(mini, cmd); // the command itself connects and redirects the input and output (itas own fd table)
		if (execve(cmd->path, cmd->args, mini->envp) == -1) // the final command that takes over the p
		{
			perror("execve");
			minishell_exit(mini, cmd);
		}
	}
	else
	{
		if (cmd->pipe_in)
		{
			close_fd(mini, cmd, cmd->pipe_in->read);
		}
		if (cmd->pipe_out)
		{
			close_fd(mini, cmd, cmd->pipe_out->write);
		}
	}
}


void    set_and_execute_pipeline(t_mini *mini, t_cmd *cmd_array)
{
	int    i;
	t_pipefd *p;

	i = 0;
	p = mini->pipes;
	while (i < mini->cmd_count - 1)
	{
		if (pipe(p->fildes) == -1)
			minishell_exit(mini, cmd_array);
		cmd_array[i].pipe_out = p;
		cmd_array[i + 1].pipe_in = p;
		p++;
		i++;
	}
	i = 0;
	while (i < mini->cmd_count)
	{
		execute_command(mini, cmd_array + i);
		i++;
	}
}
