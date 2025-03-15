

#include "../includes/minishell.h"

int	pwd()
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("get_cwd() failed\n");
		return (-1);
	}
	return (0);
}
