/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:11 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:40:12 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cat_wildcards(t_mini *mini, t_wildcard *w, char *line)
{
	char	*final_sub;

	if (is_only_specific_char(line, '*'))
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

char	*substitute_wildcard(t_mini *mini, char *line, t_wildcard *w, int i)
{
	char	*dest;

	set_wildcard(mini, line, w);
	i = get_new_index(w->wildcard);
	set_wildcard_directory(mini, w, i);
	tokenize_wildcard(mini, w, i);
	w->file_amount = count_valid_files(w);
	if (!w->file_amount)
		return (free_wildcard_struct(w), line);
	fill_file_list(mini, w);
	sort_array(w->file_list, double_array_len(w->file_list));
	change_affixes(mini, w, i);
	line = crop_command(mini, line, w);
	set_sub_token(mini, w);
	dest = cat_wildcards(mini, w, line);
	free_wildcards(line, w);
	return (dest);
}

/**Tests if a substitution is needed
 */
int	need_wildcard_substitution(char *line)
{
	int		i;
	t_quote	q;

	init_quotes(&q);
	i = -1;
	while (line[++i])
	{
		quote_enclosure_handle(line[i], &q);
		if (line[i] && line[i] == '*' && !q.dbl && !q.sgl)
		{
			if (i > 0 && line[i - 1] != 92)
				return (i);
			else if (i == 0)
				return (0);
		}
	}
	return (-1);
}

void	init_wildcard_struct(t_wildcard *w)
{
	w->wildcard = NULL;
	w->dirname = NULL;
	w->token = NULL;
	w->s_dir = NULL;
	w->prefix = NULL;
	w->suffix = NULL;
	w->temp = NULL;
	w->file_list = NULL;
	w->current = false;
}

/**Go through the command and do all the substitutions
 */
char	*wildcard_handle(t_mini *mini, char *line)
{
	int			i;
	t_wildcard	w;

	i = need_wildcard_substitution(line);
	if (i == -1)
		return (line);
	init_wildcard_struct(&w);
	line = substitute_wildcard(mini, line, &w, i);
	return (line);
}
