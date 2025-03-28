
#include "minishell.h"

void	backup_standard_fd(t_mini *mini, t_cmd *cmd)
{
	(void)cmd;
	mini->fd_backup->stdin_backup = dup(STDIN_FILENO);
	mini->fd_backup->stdin_backup = dup(STDOUT_FILENO);
}

void	restore_standard_fd(t_mini *mini, t_cmd *cmd)
{
	dup_fd(mini, cmd, mini->fd_backup->stdin_backup, STDIN_FILENO);
	dup_fd(mini, cmd, mini->fd_backup->stdout_backup, STDOUT_FILENO);
}