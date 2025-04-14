
#include "minishell.h"

t_builtin_func	get_builtin_function(t_cmd *cmd, char *cmd_name)
{
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (&builtin_cd);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		return (&builtin_echo);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (&builtin_env);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (&builtin_exit);
	else if (ft_strcmp(cmd_name, "export") == 0)
	{
		return (&builtin_export);
		cmd->is_export = 1;
	}
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (&builtin_pwd);
	// else if (ft_strcmp(cmd_name, "unset") == 0)
	// 	return (&builtin_unset);
	else
		return (NULL);
}

void	handle_builtin(t_mini *mini, t_cmd *cmd)
{
	t_builtin_func	f;

	backup_standard_fd(mini);
	if (cmd->redir_amount > 0)
	{
		setup_redirections(mini, cmd);
	}
	f = get_builtin_function(cmd, cmd->command);
	f(mini, cmd);
	restore_standard_fd(mini);
}

int	exec_mini(t_mini *mini, t_cmd *cmd)
{
	if (cmd->type == BUILTIN && mini->cmd_count == 1)
	{
		handle_builtin(mini, cmd);
	}
	if (cmd->type == USER || (cmd->type == BUILTIN && mini->cmd_count > 1)
		|| cmd->type == INVALID)
	{
		backup_standard_fd(mini);
		set_and_execute_pipeline(mini, cmd);
		restore_standard_fd(mini);
		if (mini->last_return == CMD_NOT_FOUND)
		{
			exit_minishell(mini, cmd);
		}
	}
	return (mini->last_return);
}
