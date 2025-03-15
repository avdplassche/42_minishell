
#include "../includes/minishell.h"


// void	exec_mini(t_mini *mini, t_cmd *cmd)
// {
// 	exec(mini, cmd[0]);
// 	exec(mini, cmd[1]);
// }

// pid_t	exec(t_mini *mini, t_cmd cmd)
// {
// 	(void)mini;
	
// 	int status = 0;
// 	pid_t pid = fork();
// 	if (pid == 0)
// 	{
// 		printf("i am HERE IN THE CHILD\n");
// 		execve(cmd.path, cmd.args, mini->envp);
// 	}
// 	waitpid(pid, &status, 0);
// }