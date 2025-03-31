#include "minishell.h"

void	free_wildcard_struct(t_wildcard *w)
{
	if (w->dirname)
	{
		free(w->dirname);
		w->dirname = NULL;
	}
	if (w->token)
	{
		free(w->token);
		w->token = NULL;
	}
	if (w->s_dir)
	{
		free(w->s_dir);
		w->s_dir = NULL;
	}
	if (w->prefix)
	{
		free(w->prefix);
		w->prefix = NULL;
	}
	if (w->suffix)
	{
		free(w->suffix);
		w->suffix = NULL;
	}
}


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
	if (cmd->redir)
		free(cmd->redir);
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
	{
		free_string_array(mini->envp);
		mini->envp = NULL;
	}
	if (mini->builtins)
	{
		free_string_array(mini->builtins);
		mini->builtins = NULL;
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
	if (mini->fd_in != -1)
		close(mini->fd_in);
	if (mini->fd_out != -1)
		close(mini->fd_out);
}

void	minishell_exit(t_mini *mini, t_cmd *cmd)
{
	(void)cmd;
	mini->should_exit = true;
	free_mini(mini);
}
