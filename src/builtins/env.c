/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:20 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/17 17:24:06 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_mini *mini, t_cmd *cmd)
{
	(void)cmd;
	if (!mini->envp || !*mini->envp)
	{
		return (1);
	}
	if (cmd->arg_amount >= 1)
	{
		perror("Minishell: env: too many arguments\n");
		mini->last_return = CMD_NOT_FOUND;
		return (-1);
	}
	string_array_print(cmd, mini->envp);
	return (0);
}
