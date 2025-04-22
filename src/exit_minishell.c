/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:03 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/22 17:58:21 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string_ptr(char **str)
{
	if (!(*str))
		return ;
	free(*str);
	*str = NULL;
}

void	free_cmd(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count)
	{
		free_string_ptr(&cmd[i].command);
		free_string_ptr(&cmd[i].path);
		free_string_array(&cmd[i].args);
		free_pathnames(&cmd[i]);
		i++;
	}
	if (cmd)
		free(cmd);
	cmd = NULL;
}

/** Frees t_mini mini, used when leaving minishell
 *maybe when signals exit the program
 */
void	free_mini(t_mini *mini)
{
	free_string_array(&mini->envp);
	free_string_array(&mini->export);
	free_string_array(&mini->builtins);
	free_string_array(&mini->paths);
	if (mini->pipes)
	{
		free(mini->pipes);
		mini->pipes = NULL;
	}
	if (mini->fd_backup)
	{
		if (mini->fd_backup->stdin_backup != -1)
			close(mini->fd_backup->stdin_backup);
		if (mini->fd_backup->stdout_backup != -1)
			close(mini->fd_backup->stdout_backup);
		if (mini->fd_backup)
		{
			free(mini->fd_backup);
			mini->fd_backup = NULL;
		}
	}
	free_string_ptr(&mini->line);
}

void	exit_minishell(t_mini *mini, t_cmd *cmd)
{
	if (cmd)
		free_cmd(mini, cmd);
	free_mini(mini);
	exit(mini->last_return);
}
