
#include "../includes/minishell.h"

int	builtin_pwd(t_mini *mini)
{
	(void)mini;
	
	char	cwd[PATH_MAX];
	char	*pwd_env;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		pwd_env = getenv("PWD");
		printf("%s\n", pwd_env);
	}
	else
	{
		perror("get_cwd() failed\n");
		return (-1);
	}
	return (0);
}

int main()
{
	t_mini mini;

	builtin_pwd(&mini);
	return (0);
}