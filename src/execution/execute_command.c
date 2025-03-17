
#include "../includes/minishell.h"


void	exec_mini(t_mini *mini, t_cmd *cmd)
{
	if ()
}

pid_t	exec_child(t_mini *mini, t_cmd cmd)
{
	(void)mini;
	
	int status = 0;
	pid_t pid = fork();
	if (pid == 0)
	{
		DEBUG("i am HERE IN THE CHILD\n");
		execve(cmd.path, cmd.args, mini->envp);
	}
	waitpid(pid, &status, 0);
}
