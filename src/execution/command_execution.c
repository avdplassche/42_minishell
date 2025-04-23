/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:11 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/23 19:40:44 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	validate_command(t_mini *mini, t_cmd *cmd)
{
	check_command_access(cmd);
	if (cmd->is_directory || cmd->error_access)
	{
		handle_error(mini, cmd);
		free_cmd(mini, cmd);
		free_mini(mini);
		exit(mini->last_return);
	}
}

static void	setup_execution_environment(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	int	redir_status;
	
	redir_status = 0;
	handle_heredoc(mini, cmd);
	if (cmd->command[0] == '\0')
		close_fd_backup_and_exit(mini, cmd);
	setup_command_pipes(mini, cmd, cmd_index);
	if (cmd->redir_amount > 0)
	{
		redir_status = setup_command_redirections(mini, cmd);
		if (redir_status != 0)
			close_fd_backup_and_exit(mini, cmd);
	}
}

static void	handle_command_execution(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	t_builtin_func	f;
	
	setup_execution_environment(mini, cmd, cmd_index);
	validate_command(mini, cmd);
	if (cmd->type == BUILTIN)
	{
		f = get_builtin_function(cmd, cmd->command);
		f(mini, cmd);
		exit(EXIT_SUCCESS);
	}
	if (execve(cmd->path, cmd->args, mini->envp) == -1)
	{
		printf("execve failed with errno: %d\n", errno);
		perror("execve");
		mini->last_return = MALLOC_ERROR;
		exit(EXIT_FAILURE);
	}
}

static void	fork_command_executor(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	pid_t			pid;

	pid = fork();
	if (pid == -1)
	{
		mini->last_return = MALLOC_ERROR;
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal_child();
		handle_command_execution(mini, cmd, cmd_index);
	}
	else
		cmd->pid = pid;
}

void	execute_command(t_mini *mini, t_cmd *cmd)
{
	int	cmd_index;

	cmd_index = 0;
	create_pipe_array(mini, cmd);
	setup_command_signal(mini);
	while (cmd_index < mini->cmd_count)
	{
		fork_command_executor(mini, &cmd[cmd_index], cmd_index);
		cmd_index++;
	}
	parent_closes_all_pipes(mini);
	mini->last_return = wait_for_children(mini, cmd);
	setup_command_signal(mini);
}
