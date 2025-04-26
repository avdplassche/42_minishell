/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:20:40 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 13:49:30 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_fd_backup(t_mini *mini)
{
	if (mini->stdin_backup > 0)
	{
		close(mini->stdin_backup);
		mini->stdin_backup = -1;
	}
	if (mini->stdout_backup > 0)
	{
		close(mini->stdout_backup);
		mini->stdout_backup = -1;
	}
		//restore_standard_fd(mini);
}

void	close_fd_backup_and_exit(t_mini *mini)
{
	clean_fd_backup(mini);
	exit_minishell(mini);
}
