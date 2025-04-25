/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:07:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/25 21:25:28 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_closes_all_pipes(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count - 1)
	{
		close(mini->pipes[i].read);
		close(mini->pipes[i].write);
		i++;
	}
	free(mini->pipes);
	mini->pipes = NULL;
}

void	setup_command_pipes(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	if (cmd_index > 0)
	{
		dup2_fd(mini, cmd->pipe_in->read, STDIN_FILENO);
	}
	if (cmd_index < mini->cmd_count - 1)
	{
		dup2_fd(mini, cmd->pipe_out->write, STDOUT_FILENO);
	}
	parent_closes_all_pipes(mini);
}

void	create_pipe_array(t_mini *mini)
{
	int			i;

	mini->pipes = ft_calloc((mini->cmd_count - 1), sizeof(*(mini->pipes)));
	if (!mini->pipes)
	{
		perror("Error in pipe creation:");
		mini->last_return = PIPE_ERROR;
		exit_minishell(mini);
	}
	i = 0;
	while (i < mini->cmd_count - 1)
	{
		if (pipe(mini->pipes[i].fildes) == -1)
		{
			mini->last_return = MALLOC_ERROR;
			exit_minishell(mini);
		}
		mini->cmd[i].pipe_out = &mini->pipes[i];
		mini->cmd[i + 1].pipe_in = &mini->pipes[i];
		i++;
	}
}
