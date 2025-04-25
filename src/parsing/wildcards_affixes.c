/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_affixes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:39:55 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/25 21:33:28 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sub_token(t_mini *mini, t_wildcard *w)
{
	int		len;

	len = 0;
	if (w->file_amount == 1)
	{
		free_string_ptr(&w->wildcard);
		w->wildcard = w->file_list[0];
		return ;
	}
	while (len < w->file_amount - 1)
	{
		append_space_to_string(mini, w, &w->file_list[len]);
		if (!w->file_list[len])
			free_wildcard_double_pointer_first_part(mini, w);
		len++;
	}
	free_string_ptr(&w->wildcard);
	w->wildcard = join_n_strings_wildcards(mini, w);
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
