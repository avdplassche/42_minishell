/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:39:11 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/22 11:50:52 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** Get the command's last index, use it to substring
 * @param mini t_mini structure, containing current line to work with
 * @return i : last index of the command
*/
int	get_last_index(t_mini *mini)
{
	const char	charset[5] = " <>|";
	int			i;
	t_quote		q;

	i = mini->cursor - 1;
	q.dbl = 0;
	q.sgl = 0;
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &q);
		if (contain_char(charset, mini->line[i]) && !q.sgl && !q.dbl)
			return (i);
	}
	return (i);
}

char	*get_cmd_bin(t_mini *mini)
{
	char	*temp;
	int		len;
	char	*dest;

	len = get_last_index(mini);
	temp = ft_substr(mini->line, mini->cursor, len - mini->cursor);
	str_malloc_check(mini, temp);
	mini->cursor = len;
	while (contain_char(SPACES, mini->line[len++]))
		mini->cursor++;
	if (!contain_quotes(temp))
		dest = ft_strdup(temp);
	else
		dest = clean_command_quotes(mini, temp);
	free_string_ptr(&temp);
	str_malloc_check(mini, dest);
	return (dest);
}
