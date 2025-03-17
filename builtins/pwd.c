

#include "../includes/minishell.h"

int	builtin_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*pwd_env;
	(void) mini;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		pwd_env = getenv("PWD");
		printf("%s\n", pwd_env);
		printf("%s\n", cwd);
	}

	else
	{
		perror("get_cwd() failed\n");
		return (-1);
	}
	return (0);
}
