/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:53:51 by jrandet           #+#    #+#             */
/*   Updated: 2025/03/28 11:54:34 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe_array(t_mini *mini, t_cmd *cmd_array)
{
	mini->pipes = ft_calloc((mini->cmd_count), sizeof(*(mini->pipes)));
	if (!mini->pipes)
	{
		mini->last_return = MALLOC_ERROR;
		minishell_exit(mini, cmd_array);
	}
}
