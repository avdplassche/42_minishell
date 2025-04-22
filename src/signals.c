/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:58 by jrandet           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/22 12:13:31 by jrandet          ###   ########.fr       */
=======
/*   Updated: 2025/04/22 11:23:01 by alvan-de         ###   ########.fr       */
>>>>>>> 189375cdfab270c189b0b28c0da58e9e912b67e5
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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_list(void)
{
	signal(SIGINT, handle_sigint);
	//signal(SIGQUIT, handle_sigquit);
	// signal(SIGQUIT, handle_sigquit);
	signal(SIGQUIT, SIG_IGN);
}

