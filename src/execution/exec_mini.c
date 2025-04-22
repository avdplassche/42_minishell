/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:19 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/22 17:57:40 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		cmd->is_export = 1;
		return (&builtin_export);
	}
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (&builtin_pwd);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (&builtin_unset);
	else
		return (NULL);
}

int	handle_builtin(t_mini *mini, t_cmd *cmd)
{
	t_builtin_func	f;
	int				redirection_status;

	redirection_status = 0;
	if (check_command_synthax(mini, cmd))
			return (mini->last_return);
	backup_standard_fd(mini);
	if (cmd->redir_amount > 0)
	{
		redirection_status = setup_redirections(mini, cmd);
		if (redirection_status != 0)
		{
			printf("redirection has failed\n");
			clean_fd_backup(mini, cmd);
			return (mini->last_return);
		}
	}
	f = get_builtin_function(cmd, cmd->command);
	f(mini, cmd);
	restore_standard_fd(mini);
	return (mini->last_return);
}

int set_minimal_env(t_mini *mini, t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	char	*pwd_entry;
	
	if (!ft_get_env(mini, cmd, "PATH"))
	{
		set_env(mini, "PATH",
	"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:.");
	}
	if (!ft_get_env(mini, cmd, "PWD") && getcwd(cwd, sizeof(cwd)))
	{
		pwd_entry = ft_strjoin("PWD=", cwd);
		if (!pwd_entry)
		{
			mini->last_return = 1;
			exit_minishell(mini, cmd);
		}
		set_env(mini, "PWD", pwd_entry);
		free_string_ptr(&pwd_entry);
	}
	if (!ft_get_env(mini, cmd, "SHLVL"))
		set_env(mini, "SHVL", "SHVL=1");
	return (0);
}

int	exec_mini(t_mini *mini, t_cmd *cmd)
{
	if (*mini->envp == NULL)
	{
		set_minimal_env(mini, cmd);
	}
	else if (cmd->type == BUILTIN && mini->cmd_count == 1)
	{
		return (handle_builtin(mini, cmd));
	}
	else if (cmd->type == USER || (cmd->type == BUILTIN && mini->cmd_count > 1)
		|| cmd->type == INVALID)
	{
		backup_standard_fd(mini);
		if (check_command_synthax(mini, cmd))
			return (mini->last_return);
		set_and_execute_pipeline(mini, cmd);
		restore_standard_fd(mini);
		if (mini->last_return == CMD_NOT_FOUND)
		{
			exit_minishell(mini, cmd);
		}
	}
	return (mini->last_return);
}
