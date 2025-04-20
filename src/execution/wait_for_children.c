/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:07:10 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/20 16:45:17 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_children(t_mini *mini, t_cmd *cmd)
{
	int		wstatus;
	int		exit_status;
	pid_t	w;
	int		signal_number;

	exit_status = 0;
	signal_number = 0;
	while (1)
	{
		w = waitpid (-1, &wstatus, 0);
		if (w == -1)
		{
			if (errno == ECHILD)
				break;
			if (errno == EINTR)
				continue;
			perror("waitpid");
			exit_minishell(mini, cmd);
		}
		if (WIFEXITED(wstatus) && !signal_number)
		{
			exit_status = WEXITSTATUS(wstatus);
		}
		else if (WIFSIGNALED(wstatus))
		{
			signal_number = 1;
			exit_status  = 128 + WTERMSIG(wstatus);
		}
	}
	return (exit_status);
}
