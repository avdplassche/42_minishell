#include "minishell.h"

void	free_cmd(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count)
	{
		if (cmd[i].command != NULL)
		{
			free(cmd[i].command);
			cmd[i].command = NULL;
		}
		if (cmd[i].path != NULL)
		{
			free(cmd[i].path);
			cmd[i].path = NULL;
		}
		if (cmd[i].args != NULL)
		{
			free_string_array(cmd[i].args);
			cmd[i].args = NULL;
		}
		i++;
	}
	if (cmd)
		free(cmd);
}

/** Frees char ** variables
 */
void	free_string_array(char **str)
{
	int	i;

	if (!(str))
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/** Frees t_mini mini, used when leaving minishell
 *maybe when signals exit the program
 */
void	free_mini(t_mini *mini)
{
	if (mini->envp)
		free_string_array(mini->envp);
	if (mini->builtins)
		free_string_array(mini->builtins);
	if (mini->paths)
		free_string_array(mini->paths);
	if (mini->pipes)
		free(mini->pipes);
	if (mini->fd_backup)
	{
		if (mini->fd_backup->stdin_backup != -1)
			close(mini->fd_backup->stdin_backup);
		if (mini->fd_backup->stdout_backup != -1)
			close(mini->fd_backup->stdout_backup);
		if (mini->fd_backup->stderr_backup != -1)
			close(mini->fd_backup->stderr_backup);
		if (mini->fd_backup)
			free(mini->fd_backup);
	}
	if (mini->fd_in != -1)
		close(mini->fd_in);
	if (mini->fd_out != -1)
		close(mini->fd_out);
}

void	minishell_exit(t_mini *mini, t_cmd *cmd)
{
	free_cmd(mini, cmd);
	cmd = NULL;
	free_mini(mini);
}
