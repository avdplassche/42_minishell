/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:11 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/26 17:06:06 by alvan-de         ###   ########.fr       */
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

bool	is_wildcard_cmd(char *line)
{
	int		i;
	t_quote	q;

	init_quotes(&q);
	i = -1;
	while (line[++i])
	{
		quote_enclosure_handle(line[i], &q);
		if (line[i] == ' ' && !q.dbl && !q.sgl)
			break ;
	}
	if (!line[i])
		return (true);
	return (false);
}

char	*cat_wildcards(t_mini *mini, t_wildcard *w, char *line)
{
	char	*final_sub;
	bool	cmd;

	cmd = is_wildcard_cmd(line);
	if (is_only_specific_char(line, '*') || cmd)
	{
		final_sub = ft_strdup(w->wildcard);
		str_malloc_wildcard_check(mini, w, final_sub);
		free_string_ptr(&w->wildcard);
		return (final_sub);
	}
	final_sub = ft_strjoin(line, w->wildcard);
	str_malloc_wildcard_check(mini, w, final_sub);
	free_string_ptr(&w->wildcard);
	return (final_sub);
}

char	*empty_enquote(t_mini *mini, t_wildcard *w, char *line, int i)
{
	int		j;
	char	*line_out;

	while (i > 0 && line[i] != ' ')
		i--;
	if (i > 0)
		w->prefix = ft_substr(line, 0, ++i);
	if (i > 0)
		str_malloc_wildcard_check(mini, w, w->prefix);
	j = i;
	while (line[j] && line[j] != ' ')
		j++;
	w->temp = ft_substr(line, i, j - i);
	str_malloc_wildcard_check(mini, w, w->temp);
	w->wildcard = enquote_str(w->temp, 34);
	str_malloc_wildcard_check(mini, w, w->wildcard);
	if (line[j])
		w->suffix = ft_substr(line, j, ft_strlen(line) - j);
	if (line[j])
		str_malloc_wildcard_check(mini, w, w->suffix);
	line_out = join_three_strings(w->prefix, w->wildcard, w->suffix);
	str_malloc_wildcard_check(mini, w, line_out);
	free(line);
	free_wildcard_struct(w);
	return (line_out);
}

char	*substitute_wildcard(t_mini *mini, char *line, t_wildcard *w, int i)
{
	char	*dest;

	set_line_suffix(mini, line, w, i);
	set_wildcard(mini, line, w, i);
	i = get_new_index(w->wildcard);
	set_wildcard_directory(mini, w, i);
	tokenize_wildcard(mini, w, i);
	w->file_amount = count_valid_files(w);
	if (!w->file_amount)
	{
		i = need_wildcard_substitution(line);
		return (free_wildcard_struct(w), empty_enquote(mini, w, line, i));
	}
	fill_file_list(mini, w);
	sort_array(w->file_list, double_array_len(w->file_list));
	change_affixes(mini, w, i);
	line = crop_command(mini, line, w);
	set_sub_token(mini, w);
	dest = cat_wildcards(mini, w, line);
	if (w->line_suffix)
		dest = add_line_suffix(mini, dest, w);
	free_wildcards(line, w);
	return (dest);
}
