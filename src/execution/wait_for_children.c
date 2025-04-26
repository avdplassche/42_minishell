/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:07:10 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 17:01:24 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static void	handle_fork_signal(int *sig_number, int *exit_status, int wstatus)
{
	*sig_number = 1;
	*exit_status = 128 + WTERMSIG(wstatus);
	if (WTERMSIG(wstatus) == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	else if (WTERMSIG(wstatus) == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
}

static int	handle_waitpid_error(t_mini *mini, int errno_value)
{
	if (errno_value == ECHILD)
		return (1);
	if (errno_value == EINTR)
		return (0);
	perror("waitpid");
	exit_minishell(mini);
	return (0);
}

int	wait_for_children(t_mini *mini)
{
	int		wstatus;
	int		exit_status;
	pid_t	w;
	int		sig_number;
	int		i;

	exit_status = 0;
	sig_number = 0;
	i = 0;
	while (i < mini->cmd_count)
	{
		w = waitpid(mini->cmd[i].pid, &wstatus, 0);
		if (w == -1 && handle_waitpid_error(mini, errno))
			break ;
		if (WIFEXITED(wstatus) && !sig_number)
			exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			handle_fork_signal(&sig_number, &exit_status, wstatus);
		i++;
	}
	return (exit_status);
}
