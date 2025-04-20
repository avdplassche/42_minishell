/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:11 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/20 12:48:09 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_fd_backup(t_mini *mini, t_cmd *cmd)
{
	if (mini->fd_backup)
	{
		if (mini->fd_backup->stdin_backup > 0)
			close(mini->fd_backup->stdin_backup);
		if (mini->fd_backup->stdout_backup > 0)
			close(mini->fd_backup->stdout_backup);
		free_cmd(mini, cmd);
		free_mini(mini);
	}
	exit(EXIT_FAILURE);
}

static void	handle_command_execution(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	t_builtin_func	f;
	
	process_all_heredocs(mini, cmd);
	connect_command_pipeline(mini, cmd, cmd_index);
	if (cmd->redir_amount > 0)
		setup_redirections(mini, cmd);
	check_access(cmd);
	if (cmd->type == BUILTIN)
	{
		f = get_builtin_function(cmd, cmd->command);
		f(mini, cmd);
		exit(EXIT_SUCCESS);
	}
	if (cmd->is_directory || cmd->error_access)
	{
		handle_errno_message(mini, cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd->path, cmd->args, mini->envp) == -1)
	{
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
		handle_command_execution(mini, cmd, cmd_index);
	else
		cmd->pid = pid;
}

static void	create_pipes(t_mini *mini, t_cmd *cmd)
{
	int			i;

	mini->pipes = ft_calloc((mini->cmd_count - 1), sizeof(*(mini->pipes)));
	if (!mini->pipes)
	{
		mini->last_return = MALLOC_ERROR;
		exit_minishell(mini, cmd);
	}
	i = 0;
	while (i < mini->cmd_count - 1)
	{
		if (pipe(mini->pipes[i].fildes) == -1)
		{
			mini->last_return = MALLOC_ERROR;
			exit_minishell(mini, cmd);
		}
		cmd[i].pipe_out = &mini->pipes[i];
		cmd[i + 1].pipe_in = &mini->pipes[i];
		i++;
	}
}

void	set_and_execute_pipeline(t_mini *mini, t_cmd *cmd)
{
	int	cmd_index;

	cmd_index = 0;
	create_pipes(mini, cmd);
	while (cmd_index < mini->cmd_count)
	{
		fork_command_executor(mini, &cmd[cmd_index], cmd_index);
		cmd_index++;
	}
	parent_closes_all_pipes(mini);
	mini->last_return = wait_for_children(mini, cmd);
}
