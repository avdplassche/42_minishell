
#include "minishell.h"

void	execute_command(t_mini *mini, t_cmd *cmd)
{
	char	*execution_path;

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
		minishell_exit(mini, cmd);
	}
}
