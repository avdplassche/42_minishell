

#include "minishell.h"

/*
	uses the getcwd and prints to the standard output, this is a builtin
*/
int	builtin_pwd(t_cmd *cmd, t_mini *mini)
{
	char	cwd[PATH_MAX];
	(void)cmd;

	DEBUG("entered the pwd function\n");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("get_cwd() failed\n");
		mini->last_return = CMD_NOT_FOUND;
		return (mini->last_return);
	}
	mini->last_return = 0;
	return (mini->last_return);
}
