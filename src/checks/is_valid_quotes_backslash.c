/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_quotes_backslash.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:41:02 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/16 18:36:19 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** Tests the validity of quotes with an open/closed boolean system
 * @param mini t_mini containing the command line
 * @return 1 for valid quotes, 0 for non valid
 * @note ascii 34 =  "
 * @note ascii 39 =  '
 */
int	is_valid_quote_basckslash(t_mini *mini)
{
	int		i;
	t_quote	q;

	init_quotes(&q);
	i = -1;
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &q);
		if (!q.sgl && !q.dbl && mini->line[i] == 92)
			return (print_error("minishell: backslash found\n", NULL, 2), 0);
	}
	if (q.sgl || q.dbl)
		return (print_error("minishell: quote error\n", NULL, 2), 0);
	return (1);
}
