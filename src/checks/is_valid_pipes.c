/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:58 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:40:59 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_start_of_line(t_mini *mini)
{
	if (mini->line[0] == '|')
	{
		if (mini->line[1] == '|')
			return (print_unexpected_token("||"), 0);
		else
			return (print_unexpected_token("|"), 0);
	}
	if (mini->line[ft_strlen(mini->line) - 1] == '|')
		return (print_error("minishell: pipe error\n", NULL, 2), 0);
	return (1);
}

int	is_valid_pipes(t_mini *mini)
{
	t_quote	q;
	int		i;

	i = 0;
	q.sgl = 0;
	q.dbl = 0;
	if (pipe_start_of_line(mini) == 0)
		return (0);
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &q);
		if (mini->line[i] == '|' && !q.sgl && !q.dbl)
		{
			if (mini->line[++i] == '|')
				return (0);
			i--;
		}
	}
	return (1);
}
