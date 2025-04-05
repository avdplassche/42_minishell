
#include "minishell.h"

void	dup2_fd(t_mini *mini, t_cmd *cmd, int fd_to_clone, int fd_new_clone)
{
	if (dup2(fd_to_clone, fd_new_clone) == -1)
	{
		perror("Error in dup2: ");
		exit_minishell(mini, cmd);
	}
}