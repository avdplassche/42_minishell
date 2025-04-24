/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:07:10 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/24 12:56:58 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_fork_signal(int *sig_number, int *exit_status, int wstatus)
{
	*sig_number = 1;
	*exit_status = 128 + WTERMSIG(wstatus);
	printf("exitstatus is worth %d\n", *exit_status);
	if (WTERMSIG(wstatus) == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	else if (WTERMSIG(wstatus) == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
}

int	wait_for_children(t_mini *mini, t_cmd *cmd)
{
	int		wstatus;
	int		exit_status;
	pid_t	w;
	int		sig_number;

	exit_status = 0;
	sig_number = 0;
	int i = 0;
	while (i < mini->cmd_count)
	{
		w = waitpid (cmd[i].pid, &wstatus, 0);
		if (w == -1)
		{
			if (errno == ECHILD)
				break ;
			if (errno == EINTR)
				continue ;
			perror("waitpid");
			exit_minishell(mini, cmd);
		}
		if (WIFEXITED(wstatus) && !sig_number)
			exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
		{
			printf("entered the wifsignaled function \n");
			handle_fork_signal(&sig_number, &exit_status, wstatus);
		}
		i++;
	}
	return (exit_status);
}
