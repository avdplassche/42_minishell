

#include "../includes/minishell.h"

int	builtin_pwd(t_cmd *cmd, t_mini *mini)
{
	char	cwd[PATH_MAX];
	(void)mini;
	(void)cmd;

	DEBUG("entered the pwd function\n");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		printf("%s\n", getenv("LS_COLORS"));
	}
	else
	{
		perror("get_cwd() failed\n");
		return (-1);
	}
	return (0);
}
