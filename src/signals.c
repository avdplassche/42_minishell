/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:58 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 12:02:01 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	signal_child(void)
{

}

void	signal_list(void)
{
	// struct sigaction sigint;
	// struct sigaction sigquit;
	// struct termios term;

	// tcsetattr(1,0,  &term);
	// tcgetattr(ttyslot(), &term);
	// printf("term |%hhn|\n", term.c_cc);
	// printf("%s", ioctl(0, ))
	// ioctl()
	// printf("term |%d|\n", ttyslot());
	// sigemptyset(&sigint.sa_mask);
	// sigint.sa_handler = handle_sigint;
	// sigaction(SIGINT, &sigint, NULL);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);

	// signal(SIGQUIT, handle_sigquit);
	
}


