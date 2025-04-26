/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:19:01 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 14:47:10 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_command_signal(t_mini *mini)
{
	struct sigaction	sig_ignore;

	sig_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sig_ignore.sa_mask);
	sig_ignore.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sig_ignore, NULL) == -1)
	{
		perror("sigaction: SIGQUIT");
		exit_minishell(mini);
	}
}

void	signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signal_handlers(t_mini *mini)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	(void)mini;
	sig_int.sa_handler = handler;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sig_int, NULL) == -1)
	{
		perror("sigaction: SIGINT");
		exit_minishell(mini);
	}
	sig_quit.sa_handler = SIG_IGN;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sig_quit, NULL) == -1)
	{
		perror("sigaction: SIGQUIT");
		exit_minishell(mini);
	}
}
