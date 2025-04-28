/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:19 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/28 12:32:10 by jrandet          ###   ########.fr       */
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

	if (mini->envp)
		free_string_array(&mini->envp);
	mini->envp = malloc(sizeof(char *) * 4);
	mini->envp[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:.");
	str_malloc_check(mini, mini->envp[0]);
	getcwd(cwd, sizeof(cwd));
	mini->envp[1] = ft_strjoin("PWD=", cwd);
	str_malloc_check(mini, mini->envp[1]);
	mini->envp[2] = ft_strdup("SHVL=1");
	str_malloc_check(mini, mini->envp[2]);
	mini->envp[3] = NULL;
	return (0);
}

int	exec_mini(t_mini *mini, t_cmd *cmd)
{
	backup_standard_fd(mini);
	handle_heredoc(mini, cmd);
	if (cmd->type == BUILTIN && mini->cmd_count == 1)
	{
		return (execute_builtin(mini, cmd));
	}
	if (cmd->type == USER || (cmd->type == BUILTIN && mini->cmd_count > 1)
		|| cmd->type == INVALID || cmd->type == EMPTY)
	{
		if (check_command_synthax(mini, cmd))
			return (mini->last_return);
		execute_command(mini);
		restore_standard_fd(mini);
	}
	return (mini->last_return);
}
