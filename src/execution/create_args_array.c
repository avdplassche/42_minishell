/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:14:58 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 11:55:26 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_args_array(t_mini *mini, t_cmd *cmd)
{
	cmd->args = (char **)malloc(sizeof(char *) * 2);
	if (!cmd->args)
	{
		mini->last_return = MALLOC_ERROR;
		exit(EXIT_FAILURE);
	}
	cmd->args[0] = ft_strdup(cmd->command);
	cmd->args[1] = NULL;
}
