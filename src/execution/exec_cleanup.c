/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:20:40 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/23 19:21:12 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_fd_backup(t_mini *mini, t_cmd *cmd)
{
	(void)cmd;
	if (mini->fd_backup)
	{
		if (mini->fd_backup->stdin_backup > 0)
			close(mini->fd_backup->stdin_backup);
		if (mini->fd_backup->stdout_backup > 0)
			close(mini->fd_backup->stdout_backup);
	}
}

void	close_fd_backup_and_exit(t_mini *mini, t_cmd *cmd)
{
	clean_fd_backup(mini, cmd);
	free_cmd(mini, cmd);
	free_mini(mini);
	exit(mini->last_return);
}