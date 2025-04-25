/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:37 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/25 17:16:37 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_wildcard(t_mini *mini, t_wildcard *w, int start)
{
	int		len;

	len = start;
	while (start >= 0 && w->wildcard[start] != '/'
			&& w->wildcard[start] != ' ')
		start--;
	start++;
	while (w->wildcard[len] && w->wildcard[len] != '/'
			&& w->wildcard[len] != ' ')
		len++;
	if (w->wildcard[len] == '/')
		len ++;
	w->token = ft_substr(w->wildcard, start, len - start);
	str_malloc_wildcard_check(mini, w, w->token);
}

int	is_last_asterisk(char *token, int i)
{
	while (token[i++])
		if (token[i] == '*')
			return (0);
	return (1);
}

void	set_wildcard(t_mini *mini, char *line, t_wildcard *w, int i)
{
	int	j;

	if (!contain_char(line, ' '))
	{
		w->wildcard = ft_strdup(line);
		str_malloc_check(mini, w->wildcard);
		return ;
	}
	if (i > 0)
		while (line[i - 1] != ' ')
			i--;
	else
		while (line [i] != ' ')
			i++;
	j = i;
	while (line [j] && line [j] != ' ')
		j++;
	w->wildcard = ft_substr(line, i, j - i);
	str_malloc_check(mini, w->wildcard);
}

char	*crop_command(t_mini *mini, char *line, t_wildcard *w)
{
	int		i;
	char	*line_out;
	t_quote	q;

	init_quotes(&q);
	i = -1;
	if (!contain_char(line, ' '))
		return (line);
	while (line[++i])
	{
		quote_enclosure_handle(line[i], &q);
		if (!q.dbl && !q.sgl && line[i] == '*')
			break ;
	}
	if (!line[i])
	{
		i = 0;
		while (line[i] && line[i] != ' ')
			i++;
	}
	else
	{
		while (i > 0 && line[i] != ' ')
			i--;
	}
	line_out = ft_substr(line, 0, i + 1);
	str_malloc_wildcard_check(mini, w, line_out);
	free(line);
	line = NULL;
	return (line_out);
}

int	get_new_index(char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != '*')
		i++;
	return (i);
}
