
#include "minishell.h"

void	set_sub_token(t_mini *mini, t_wildcard *w)
{
	int		len;

	len = 0;
	if (w->file_amount == 1)
	{
		w->wildcard = w->file_list[0];   //Maybe ft_strdup
		return ;
	}
	while (len < w->file_amount - 1)
	{
		append_space_to_string(mini, w, &w->file_list[len]);
		if (!w->file_list[len])
			free_wildcard_double_pointer_first_part(mini, w);
		len++;
	}
	w->wildcard = join_n_strings_wildcards(mini, w);
}

char	*cat_wildcards(char *line, char *wildcard)
{
	if (is_only_specific_char(line, '*'))
		return (ft_strdup(wildcard));
	return (ft_strjoin (line, wildcard));
}

char	*substitute_wildcard(t_mini *mini, char *line, t_wildcard *w, int i)
{
	char	*dest;

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
	dest = cat_wildcards(line, w->wildcard);
	free_wildcards(line, w->file_list, w);
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

/**Go through the command and do all the substitutions
 */
char	*wildcard_handle(t_mini *mini, char *line)
{
	int		i;
	t_wildcard	w;

	i = need_wildcard_substitution(line);
	if (i == -1)
		return (line);
	init_wildcard_struct(&w);
	set_wildcard(mini, line, &w);
	line = substitute_wildcard(mini, line, &w, i);
	return (line);
}
