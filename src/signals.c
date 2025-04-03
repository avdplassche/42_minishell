
#include "minishell.h"

void	init_signals()
{
	// sigaction();
	// sigaction(SIGINT, );
	

}

void	handle_signal(int signo)
{

	// siga
	printf("Signo : %d\n", signo);
	// if (signo == SIGINT)
	// 	printf("Signal\n\n");
	// else if (signo == SIGQUIT)
	// 	printf("End\n\n");
	// printf("sig %d\n", )

}

void	end_signal(int signo)
{
	// struct sigaction *sig;
	// printf("Signo : %d\n", signo);

	printf("Signo : %d\n", signo);

}

void	signal_list(void)
{
	struct sigaction s;

	(void)s;
	signal(SIGINT, handle_signal);
	// signal(SIGQUIT, handle_signal);
	// signal(SIGSTOP, end_signal);

}


