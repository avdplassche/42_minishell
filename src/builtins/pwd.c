/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:27:10 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 10:32:23 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_mini *mini, t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	(void)cmd;
	DEBUG("entered the pwd function\n");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("get_cwd() failed\n");
		mini->last_return = CMD_NOT_FOUND;
		return (mini->last_return);
	}
	mini->last_return = 0;
	return (mini->last_return);
}
