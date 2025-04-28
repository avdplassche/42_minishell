/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:03 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/28 11:34:14 by alvan-de         ###   ########.fr       */
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

void	free_cmd(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count)
	{
		free_string_ptr(&mini->cmd[i].command);
		free_string_ptr(&mini->cmd[i].path);
		free_string_array(&mini->cmd[i].args);
		free_pathnames(&mini->cmd[i]);
		i++;
	}
	if (mini->cmd)
		free(mini->cmd);
	mini->cmd = NULL;
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
	if (mini->stdin_backup != -1)
	{
		close(mini->stdin_backup);
		mini->stdin_backup = -1;
	}
	if (mini->stdout_backup != -1)
	{
		close(mini->stdout_backup);
		mini->stdout_backup = -1;
	}
	free_string_ptr(&mini->line);
}

void	exit_minishell(t_mini *mini)
{
	free_cmd(mini);
	free_mini(mini);
	DEBUG("mini last return before exit is worth %d\n", mini->last_return);
	exit(mini->last_return);
}
