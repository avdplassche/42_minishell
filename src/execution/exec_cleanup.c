/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:20:40 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/25 21:42:12 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_fd_backup(t_mini *mini)
{
	if (mini->fd_backup)
	{
		if (mini->fd_backup->stdin_backup > 0)
		{
			close(mini->fd_backup->stdin_backup);
			mini->fd_backup->stdin_backup = -1;
		}
		if (mini->fd_backup->stdout_backup > 0)
		{
			close(mini->fd_backup->stdout_backup);
			mini->fd_backup->stdout_backup = -1;
		}
	}
}

void	close_fd_backup_and_exit(t_mini *mini)
{
	clean_fd_backup(mini);
	exit_minishell(mini);
}
