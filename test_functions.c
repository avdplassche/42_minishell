

#include "includes/minishell.h"

/**
 * this file is here to test if created functions are working as intended
 */

int	dup_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	printf("%d\n", i);
	return (i);
}

int main(int argc, char **argv, char **envp)
{
	int fd;

	// env = NULL;
	
	printf("%d\n", dup_env(envp));
}
