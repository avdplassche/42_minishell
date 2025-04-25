/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command_access.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:01:10 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/25 21:50:47 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_command_access(t_cmd *cmd)
{
	errno = 0;
	if (cmd->type == BUILTIN)
	{
		cmd->error_access = 0;
		return ;
	}
	if (cmd->is_directory)
	{
		cmd->error_access = EISDIR;
		return ;
	}
	if (cmd->type == INVALID)
	{
		return ;
	}
	access(cmd->path, F_OK | X_OK);
	cmd->error_access = errno;
	errno = 0;
}

void	print_and_set_error(t_mini *mini, t_cmd *cmd, char *error, int erno)
{
	print_error(error, cmd->command, 2);
	mini->last_return = erno;
	clean_fd_backup(mini);
}

int	check_command_synthax(t_mini *mini, t_cmd *cmd)
{
	if (is_only_specific_char(mini->line, '%'))
	{
		print_and_set_error(mini, cmd, "minishell: fg: %s: no such job\n", 2);
		return (1);
	}
	else if (!ft_strcmp(cmd->command, "."))
	{
		print_and_set_error(mini, cmd,
			"minishell .: filename argument required\n", 2);
		return (1);
	}
	else if (is_only_specific_char(mini->line, 34)
		|| is_only_specific_char(mini->line, 39))
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return (1);
	}
	return (0);
}

void	handle_error(t_mini *mini, t_cmd *cmd)
{
	if (cmd->error_access == EISDIR)
	{
		print_error("Minishell: %s: Is a directory.\n", cmd->command, 2);
		mini->last_return = 126;
	}
	else if (cmd->error_access == ENOENT)
	{
		print_error("Minishell: %s: No such file or directory.\n",
			cmd->command, 2);
		mini->last_return = 127;
	}
	else if (cmd->error_access == EACCES)
	{
		print_error("Minishell: %s: Permission denied.\n", cmd->command, 2);
		mini->last_return = 127;
	}
	else if (cmd->type == INVALID || )
	{
		print_error("Minishell: %s: command not found.\n", cmd->command, 2);
		mini->last_return = 127;
	}
	clean_fd_backup(mini);
}
