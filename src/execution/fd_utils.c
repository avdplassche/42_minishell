
#include "minishell.h"

void	close_fd(t_mini *mini, t_cmd *cmd, int fd)
{
	if (close(fd) == -1)
	{
		perror("Invalid file descriptor in close_fd");
		minishell_exit(mini, cmd);
	}
}

void	dup_fd(t_mini *mini, t_cmd *cmd, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		minishell_exit(mini, cmd);
	close_fd(mini, cmd, oldfd);
}
