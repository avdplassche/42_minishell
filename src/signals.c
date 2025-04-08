
#include "minishell.h"


void	handle_sigint(int sig)
{
	(void)sig;
	// siga
	// printf("Signo : \n");
	readline("Prompt minishell ");
	// if (signo == SIGINT)
	// 	printf("Signal\n\n");
	// else if (signo == SIGQUIT)
	// 	printf("End\n\n");
	// printf("sig %d\n", )

}

void	handle_sigquit(int sig)
{
	(void)sig;
	// siga
	printf("Signoquit : \n");
	// if (signo == SIGINT)
	// 	printf("Signal\n\n");
	// else if (signo == SIGQUIT)
	// 	printf("End\n\n");
	// printf("sig %d\n", )

}

void	signal_list(void)
{
	struct sigaction sigint;
	struct sigaction sigquit;

	sigint.sa_flags = 0;
	sigint.sa_handler = handle_sigint;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL); //ctrl - c
	sigquit.sa_flags = 0;
	sigquit.sa_handler = handle_sigquit;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL); //ctrl - backslash
	
}


