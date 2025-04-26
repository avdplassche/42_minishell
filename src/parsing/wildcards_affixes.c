/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_affixes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:39:55 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/26 12:54:16 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_line_suffix(t_mini *mini, char *line, t_wildcard *w, int i)
{
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i])
	{
		w->line_suffix = ft_substr(line, i, ft_strlen(line) - i);
		str_malloc_wildcard_check(mini, w, w->line_suffix);
	}
}

char	*add_line_suffix(t_mini *mini, char *dest, t_wildcard *w)
{
	char	*temp;

	temp = ft_strjoin(dest, w->line_suffix);
	free(dest);
	str_malloc_wildcard_check(mini, w, temp);
	dest = ft_strdup(temp);
	free(temp);
	str_malloc_wildcard_check(mini, w, dest);
	return (dest);
}

void	get_prefix(t_mini *mini, t_wildcard *w, int i)
{
	while (i >= 0 && w->wildcard[i] != '/')
		i--;
	if (w->current)
		return ;
	else if (i == 0)
		w->prefix = ft_strdup(w->dirname);
	else
		w->prefix = ft_strjoin(w->dirname, "/");
	str_malloc_wildcard_check(mini, w, w->prefix);
}

void	get_suffix(t_mini *mini, t_wildcard *w, int i)
{
	int	len;

	len = ft_strlen(w->wildcard) - 1;
	while (i <= len && w->wildcard[i] != '/')
		i++;
	if (w->wildcard[len] == '/')
		w->suffix = ft_strdup("/");
	else if (w->wildcard[i] == '/' && i < len)
		w->suffix = ft_substr(w->wildcard, i, len - i + 1);
	else
		return ;
	str_malloc_wildcard_check(mini, w, w->suffix);
}

void	change_affixes(t_mini *mini, t_wildcard *w, int i)
{
	int		len;
	int		j;

	j = -1;
	len = double_array_len(w->file_list);
	get_prefix(mini, w, i);
	get_suffix(mini, w, i);
	while (++j < len)
	{
		w->temp = ft_strdup(w->file_list[j]);
		str_malloc_wildcard_check(mini, w, w->temp);
		free(w->file_list[j]);
		w->file_list[j] = join_three_strings(w->prefix, w->temp, w->suffix);
		if (!w->file_list[j])
			free_wildcard_double_pointer_first_part(mini, w);
		free(w->temp);
		w->temp = NULL;
	}
}
