/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:11 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/25 21:29:08 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	validate_command(t_mini *mini, t_cmd *cmd)
{
	check_command_access(cmd);
	if (cmd->is_directory || cmd->error_access || cmd->type == INVALID)
	{
		handle_error(mini, cmd);
		close_fd_backup_and_exit(mini);
	}
}

static void	setup_execution_environment(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	int	redir_status;

	redir_status = 0;
	//handle_heredoc(mini, cmd);
	if (cmd->command[0] == '\0')
		close_fd_backup_and_exit(mini);
	setup_command_pipes(mini, cmd, cmd_index);
	if (cmd->redir_amount > 0)
	{
		redir_status = setup_command_redirections(mini, cmd);
		if (redir_status != 0)
			close_fd_backup_and_exit(mini);
	}
}
 
static void	handle_command_execution(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	t_builtin_func	f;

	validate_command(mini, cmd);
	setup_execution_environment(mini, cmd, cmd_index);
	if (cmd->type == BUILTIN)
	{
		f = get_builtin_function(cmd, cmd->command);
		f(mini, cmd);
		DEBUG("entered the builtin section\n");
		exit_minishell(mini);
	}
	DEBUG("mini->last return is worth %d\n", mini->last_return);
	if (execve(cmd->path, cmd->args, mini->envp) == -1)
	{
		exit_minishell(mini);
	}
}

static void	fork_command_executor(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	pid_t			pid;

	pid = fork();
	if (pid == -1)
	{
		perror("ERROR: forking child process failed:\n");
		mini->last_return = FORK_ERROR;
		exit_minishell(mini);
	}
	if (pid == 0)
	{
		signal_child();
		handle_command_execution(mini, cmd, cmd_index);
	}
	else
		cmd->pid = pid;
}

void	execute_command(t_mini *mini)
{
	int	cmd_index;

	cmd_index = 0;

	create_pipe_array(mini);
	setup_command_signal(mini);
	while (cmd_index < mini->cmd_count)
	{
		fork_command_executor(mini, &mini->cmd[cmd_index], cmd_index);
		cmd_index++;
	}
	mini->last_return = wait_for_children(mini);
	parent_closes_all_pipes(mini);
	setup_command_signal(mini);
}
