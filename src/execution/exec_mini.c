/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:19 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/25 21:35:18 by jrandet          ###   ########.fr       */
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

int	execute_builtin(t_mini *mini, t_cmd *cmd)
{
	t_builtin_func	f;
	int				redirection_status;

	redirection_status = 0;
	if (check_command_synthax(mini, cmd))
		return (mini->last_return);
	if (cmd->redir_amount > 0)
	{
		redirection_status = setup_command_redirections(mini, cmd);
		if (redirection_status != 0)
		{
			clean_fd_backup(mini);
			return (mini->last_return);
		}
	}
	f = get_builtin_function(cmd, cmd->command);
	f(mini, cmd);
	restore_standard_fd(mini);
	return (mini->last_return);
}

int	set_minimal_env(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*pwd_entry;

	if (!ft_get_env(mini, "PATH"))
	{
		set_env(mini, "PATH",
			"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:.");
	}
	if (!ft_get_env(mini, "PWD") && getcwd(cwd, sizeof(cwd)))
	{
		pwd_entry = ft_strjoin("PWD=", cwd);
		if (!pwd_entry)
		{
			mini->last_return = 1;
			exit_minishell(mini);
		}
		set_env(mini, "PWD", pwd_entry);
		free_string_ptr(&pwd_entry);
	}
	if (!ft_get_env(mini, "SHLVL"))
		set_env(mini, "SHVL", "SHVL=1");
	return (0);
}

int	exec_mini(t_mini *mini, t_cmd *cmd)
{
	if (*mini->envp == NULL)
	{
		set_minimal_env(mini);
	}
	backup_standard_fd(mini);
	handle_heredoc(mini, cmd);
	if (cmd->type == BUILTIN && mini->cmd_count == 1)
	{
		return (execute_builtin(mini, cmd));
	}
	else if (cmd->type == USER || (cmd->type == BUILTIN && mini->cmd_count > 1)
		|| cmd->type == INVALID)
	{
		if (check_command_synthax(mini, cmd))
			return (mini->last_return);
		execute_command(mini);
		restore_standard_fd(mini);
	}
	return (mini->last_return);
}
