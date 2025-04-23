/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:32 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/23 17:17:14 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(t_cmd *cmd, int no_print_new_line, int i)
{
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!no_print_new_line)
		ft_putchar_fd('\n', 1);
}

int	builtin_echo(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	j;
	int	no_print_new_line;

	(void)mini;
	i = 1;
	no_print_new_line = 0;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		j = 1;
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] != '\0')
			break ;
		no_print_new_line = 1;
		i++;
	}
	print_echo(cmd, no_print_new_line, i);
	return (mini->last_return);
}
