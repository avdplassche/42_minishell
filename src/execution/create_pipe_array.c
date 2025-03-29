/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:53:51 by jrandet           #+#    #+#             */
/*   Updated: 2025/03/29 17:31:20 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe_array(t_mini *mini, t_cmd *cmd_array)
{
	mini->pipes = ft_calloc((mini->cmd_count - 1), sizeof(*(mini->pipes)));
	if (!mini->pipes)
	{
		mini->last_return = MALLOC_ERROR;
		minishell_exit(mini, cmd_array);
	}
}
