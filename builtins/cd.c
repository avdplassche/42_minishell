
#include "../includes/minishell.h"

//cd with only a relative or absolute pat

int	builtin_cd(t_cmd *cmd, t_mini *mini)
{
	char	*path;

	path = cmd->args[1];
	if (path == NULL || ft_strlen(path) == 0)
	{
		perror("path is invalid\n");
		return (-1);
	}
	if (chdir(path) == 0)
	{
		printf("succesfully changed directory.\n");
		builtin_pwd(cmd, mini);
	}
	return (0);
}
