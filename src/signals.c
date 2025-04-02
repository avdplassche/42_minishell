
#include "minishell.h"

void	init_signals()
{
	// sigaction()
	// sigaction(SIGINT, );

}

void	handle_signal()
{

	// siga
	printf("Signal\n\n");
	// printf("sig %d\n", )

}

void	end_signal()
{
	// struct sigaction *sig;

	printf("End Signal\n\n");

}

void	signal_list()
{
	// struct sigaction = NULL;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, end_signal);

}


