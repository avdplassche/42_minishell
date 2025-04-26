/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_backup_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:28 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 13:37:55 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backup_standard_fd(t_mini *mini)
{
	if (mini->stdin_backup == -1)
		mini->stdin_backup = dup(STDIN_FILENO);
	if (mini->stdout_backup == -1)
		mini->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_standard_fd(t_mini *mini)
{
	if (!mini)
		return ;;
	if (mini->stdin_backup >= 0)
	{
		dup2(mini->stdin_backup, STDIN_FILENO);
		close(mini->stdin_backup);
		mini->stdin_backup = -1;
	}
	if (mini->stdout_backup >= 0)
	{
		dup2(mini->stdout_backup, STDOUT_FILENO);
		close(mini->stdout_backup);
		mini->stdout_backup = -1;
	}
}
