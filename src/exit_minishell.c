#include "minishell.h"

void	free_string_ptr(char *str)
{
	free(str);
	str = NULL;
}

void	free_cmd(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count)
	{
		if (cmd[i].command != NULL)
		{
			free_string_ptr(cmd[i].command);
		}
		if (cmd[i].path != NULL)
		{
			free_string_ptr(cmd[i].path);
			// cmd[i].path = NULL;
		}
		if (cmd[i].args != NULL)
		{
			free_string_array(cmd[i].args);
			// cmd[i].args = NULL;
		}
		if (cmd[i].redir)
			free_pathnames(cmd[i]);
		i++;
	}
	if (cmd)
		free(cmd);
}

/** Frees t_mini mini, used when leaving minishell
 *maybe when signals exit the program
 */
void	free_mini(t_mini *mini)
{
	if (mini->envp)
	{
		free_string_array(mini->envp);
		// mini->envp = NULL;
	}
	if (mini->builtins)
	{
		free_string_array(mini->builtins);
		// mini->builtins = NULL;
	}
	if (mini->paths)
	{
		free_string_array(mini->paths);
		mini->paths = NULL;
	}
	if (mini->pipes)
	{
		free(mini->pipes);
		mini->pipes = NULL;
	}
	if (mini->fd_backup)
	{
		if (mini->fd_backup->stdin_backup != -1)
			close(mini->fd_backup->stdin_backup);
		if (mini->fd_backup->stdout_backup != -1)
			close(mini->fd_backup->stdout_backup);
		if (mini->fd_backup)
		{
			free(mini->fd_backup);
			mini->fd_backup = NULL;
		}
	}
	if (mini->line)
	{
		free(mini->line);
		mini->line = NULL;
	}
}

void	free_dollar_alloc(t_mini *mini)
{
	if (mini->alloc.line_out)
		free_string_ptr(mini->alloc.line_out);
	if (mini->alloc.prefix)
		free_string_ptr(mini->alloc.prefix);
	if (mini->alloc.suffix)
		free_string_ptr(mini->alloc.suffix);
	if (mini->alloc.number)
		free_string_ptr(mini->alloc.number);
	if (mini->alloc.temp)
		free_string_ptr(mini->alloc.temp);
	if (mini->alloc.var_name)
		free_string_ptr(mini->alloc.var_name);
	if (mini->alloc.var_env)
		free_string_ptr(mini->alloc.var_env);
	if (mini->alloc.var_value)
		free_string_ptr(mini->alloc.var_value);
}


void	exit_minishell(t_mini *mini, t_cmd *cmd)
{
	(void)cmd;
	mini->should_exit = true;
	free_dollar_alloc(mini);
	if (cmd)
		free_cmd(mini, cmd);
	free_mini(mini);
}
