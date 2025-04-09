
#include "minishell.h"

char	*get_sub_token(char **file_list, int file_amount)
{
	int		len;
	char	*str;

	len = 0;
	if (file_amount == 1)
		return (file_list[0]);
	while (len < file_amount - 1)
	{
		append_space_to_string(&file_list[len]);
		len++;
	}
	str = join_n_strings(file_list, file_amount);
	return (str);
}

char	*cat_wildcards(char *line, char *wildcard)
{
	if (is_only_specific_char(line, '*'))
		return (ft_strdup(wildcard));
	return (ft_strjoin (line, wildcard));
}

char	*substitute_wildcard(t_mini *mini, char *line, t_wildcard *w, int i)
{
	char		**file_list;
	char		*dest;

	i = get_new_index(w->wildcard);
	set_wildcard_directory(mini, w, w->wildcard, i);
	tokenize_wildcard(mini, w, w->wildcard, i);
	w->file_amount = count_valid_files(w);
	if (!w->file_amount)
		return (free(w->wildcard), free_wildcard_struct(w), line);
	file_list = fill_file_list(w);
	sort_array(file_list, double_array_len(file_list));
	change_affixes(file_list, w->wildcard, w, i);
	line = crop_command(line);
	free(w->wildcard);
	w->wildcard = get_sub_token(file_list, w->file_amount);
	dest = cat_wildcards(line, w->wildcard);
	free_wildcards(line, w->wildcard, file_list, w);
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
