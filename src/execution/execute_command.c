
#include "minishell.h"

void	execute_command(t_mini *mini)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		minishell_exit(mini, cmd);
	if (cmd->pid != 0)
	{
		// if there is a pipe inside comming from the right
		// 
	}
	//connect the pipes
	//path is already found 
	if (execve(cmd->path, cmd->args, mini->envp) == -1)
	{
		perror("execve");
		//need to use the exit function that i need to code
	}
}
