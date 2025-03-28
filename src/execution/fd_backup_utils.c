
#include "minishell.h"

void	backup_standard_fd(t_mini *mini)
{
	mini->fd_backup->stdin_backup = dup(STDIN_FILENO);
	mini->fd_backup->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_standard_fd(t_mini *mini)
{
	dup2(mini->fd_backup->stdin_backup, STDIN_FILENO);
	close(mini->fd_backup->stdin_backup);
	dup2(mini->fd_backup->stdout_backup, STDOUT_FILENO);
	close(mini->fd_backup->stdout_backup);
}