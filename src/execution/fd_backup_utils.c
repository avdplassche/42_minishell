/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_backup_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:28 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 12:45:57 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backup_standard_fd(t_mini *mini)
{
	mini->fd_backup->stdin_backup = dup(STDIN_FILENO);
	mini->fd_backup->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_standard_fd(t_mini *mini)
{
	if (!mini)
		return ;
	if (!mini->fd_backup)
		return ;
	if (mini->fd_backup->stdin_backup >= 0)
	{
		dup2(mini->fd_backup->stdin_backup, STDIN_FILENO);
		close(mini->fd_backup->stdin_backup);
	}
	if (mini->fd_backup->stdout_backup >= 0)
	{
		dup2(mini->fd_backup->stdout_backup, STDOUT_FILENO);
		close(mini->fd_backup->stdout_backup);
	}
}
