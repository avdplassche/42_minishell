/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_backslash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:55 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:40:56 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_backslash(t_mini *mini)
{
	int			i;
	const char	set[8] = "'\'';'";
	t_quote		q;

	i = -1;
	q.sgl = 0;
	q.dbl = 0;
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &q);
		if (!(contain_char(set, mini->line[i]) && !q.dbl && !q.sgl))
			return (1);
	}
	return (printf("minishell: aritmetic error\n"), 0);
}
