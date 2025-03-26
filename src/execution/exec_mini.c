
#include "minishell.h"

static t_builtin_func	get_builtin_function(char *cmd_name)
{
	DEBUG("entered the get_builtin function\n");
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (&builtin_cd);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		return (&builtin_echo);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (&builtin_env);
	// else if (ft_strcmp(cmd_name, "exit") == 0)
	// 	return (&builtin_exit);
	// else if (ft_strcmp(cmd_name, "export"))
	// 	return (&builtin_export);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (&builtin_pwd);
	// else if (ft_strcmp(cmd_name, "unset"))
	// 	return (&builtin_unset);
	else
		return (NULL);
}

void	exec_mini(t_mini *mini, t_cmd *cmd)
{
	t_builtin_func	f;

	DEBUG("cmd type is %d\n", cmd->type);
	if (cmd->type == BUILTIN)
	{
		f = get_builtin_function(cmd->command);
		f(cmd, mini);
		return ;
	}
	else if (cmd->type == USER)
	{
		create_pipe_array()
		execute_command(mini, cmd);
	}
	else if (cmd->type == INVALID)
	{
		//exit the shell
	}
}

/*pid_t	exec_child(t_mini *mini, t_cmd cmd)
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
}*/
