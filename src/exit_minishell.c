/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:03 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 12:01:07 by jrandet          ###   ########.fr       */
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

void	str_malloc_check(t_mini *mini, char *str)
{
	if (!str)
		exit_minishell(mini, mini->cmd);
}

void	dbl_str_malloc_check(t_mini *mini, char **str)
{
	if (!str)
		exit_minishell(mini, mini->cmd);
}


void	free_cmd(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count)
	{
		free_string_ptr(&cmd[i].command);
		cmd[i].command = NULL;
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

// void	free_dollar_alloc(t_mini *mini)
// {
// 	if (mini->alloc.line_out)
// 		free_string_ptr(mini->alloc.line_out);
// 	if (mini->alloc.prefix)
// 		free_string_ptr(mini->alloc.prefix);
// 	if (mini->alloc.suffix)
// 		free_string_ptr(mini->alloc.suffix);
// 	if (mini->alloc.number)
// 		free_string_ptr(mini->alloc.number);
// 	if (mini->alloc.temp)
// 		free_string_ptr(mini->alloc.temp);
// 	if (mini->alloc.var_name)
// 		free_string_ptr(mini->alloc.var_name);
// 	if (mini->alloc.var_env)
// 		free_string_ptr(mini->alloc.var_env);
// 	if (mini->alloc.var_value)
// 		free_string_ptr(mini->alloc.var_value);
// }

void	exit_minishell(t_mini *mini, t_cmd *cmd)
{
	if (cmd)
		free_cmd(mini, cmd);
	free_mini(mini);
	exit(mini->last_return);
}
