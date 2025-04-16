/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:07:10 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 11:07:13 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_children(t_mini *mini, t_cmd *cmd)
{
	int	wstatus;
	int	i;
	int	exit_status;

	i = 0;
	while (i < mini->cmd_count)
	{
		waitpid(cmd[i].pid, &wstatus, 0);
		exit_status = WEXITSTATUS(wstatus);
		if (exit_status == CMD_NOT_FOUND)
		{
			free_cmd(mini, cmd);
			free_mini(mini);
		}
		i++;
	}
	return (exit_status);
}
