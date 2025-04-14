/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:41:07 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:56:28 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_angle_bracket(t_mini *mini, char bracket)
{
	int		i;
	int		c;
	t_quote	q;

	init_quotes(&q);
	c = 0;
	i = 0;
	while (mini->line[i])
	{
		c = 0;
		quote_enclosure_handle(mini->line[i], &q);
		while (mini->line[i] && !q.sgl && !q.dbl
			&& (mini->line[i] == bracket))
		{
			i++;
			if (++c == 3)
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_valid_redirections(t_mini *mini)
{
	if (!is_valid_angle_bracket(mini, '<'))
		return (print_unexpected_token("<<"), 0);
	if (!is_valid_angle_bracket(mini, '>'))
		return (print_unexpected_token(">>"), 0);
	return (1);
}
