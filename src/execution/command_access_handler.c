/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:01:10 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/22 17:02:01 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_access(t_cmd *cmd)
{
	errno = 0;

	DEBUG("path is worth %s\n", cmd->path);
	if (cmd->type == BUILTIN)
		return ;
	if (cmd->is_directory)
	{
		cmd->error_access = EISDIR;
		return ;
	}
	access(cmd->path, F_OK | X_OK);
	cmd->error_access = errno;
	errno = 0;
}

void	handle_errno_message(t_mini *mini, t_cmd *cmd)
{
	if (cmd->error_access == EISDIR)
	{
		print_error("Minishell: %s: Is a directory.\n", cmd->command, 2);
		mini->last_return = 126;
	}
	else if (cmd->error_access == ENOENT)
	{
		print_error("Minishell: %s: No such file or directory.\n", cmd->command, 2);
		mini->last_return = 127;
	}
	else if (cmd->error_access == EACCES)
	{
		print_error("Minishell: %s: Permission denied.\n", cmd->command, 2);
		mini->last_return = 127;
	}
	else if (cmd->type == INVALID)
	{
		print_error("Minishell: %s: command not found.\n", cmd->command, 2);
		mini->last_return = 127;
	}
	clean_fd_backup(mini, cmd);
}