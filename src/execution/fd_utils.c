/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:36 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 11:06:40 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_fd(t_mini *mini, t_cmd *cmd, int fd_to_clone, int fd_new_clone)
{
	if (dup2(fd_to_clone, fd_new_clone) == -1)
	{
		perror("Error in dup2: ");
		exit_minishell(mini, cmd);
	}
}
