
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

char	*cat_wildcards(char *temp, char *temp2)
{
	if (is_only_specific_char(temp, '*'))
		return (ft_strdup(temp2));
	return (ft_strjoin (temp, temp2));
}

char	*substitute_wildcard(char *temp, char *temp2, int i)
{
	t_wildcard		w;
	char			**file_list;
	char			*dest;

	i = get_new_index(temp2);
	init_wildcard_struct(&w);
	set_wildcard_directory(&w, temp2, i);
	tokenize_wildcard(&w, temp2, i);
	if (!w.token)
		return (NULL);
	w.file_amount = count_valid_files( w);
	if (!w.file_amount)
		return (free(temp2), free_wildcard_struct(&w), temp);
	file_list = fill_file_list( w);
	sort_array(file_list, double_array_len(file_list));
	change_affixes(file_list, temp2, &w, i);
	temp = crop_command(temp);
	free(temp2);
	temp2 = get_sub_token(file_list, w.file_amount);
	dest = cat_wildcards(temp, temp2);
	free_wildcards(temp, temp2, file_list, &w);
	return (dest);
}

/**Tests if a substitution is needed
 */
int	need_wildcard_substitution(char *temp)
{
	int		i;
	t_quote	q;

	q.sgl = 0;
	q.dbl = 0;
	i = -1;
	while (temp[++i])
	{
		quote_enclosure_handle(temp[i], &q);
		if (temp[i] && temp[i] == '*' && !q.dbl && !q.sgl)
		{
			if (i > 0 && temp[i - 1] != 92)
				return (i);
			else if (i == 0)
				return (0);
		}
	}
	return (-1);
}

/**Go through the command and do all the substitutions
 */
char	*wildcard_handle(char *temp)
{
	int		i;
	char	*wildcard;

	i = need_wildcard_substitution(temp);
	if (i == -1)
		return (temp);
	wildcard = crop_args(temp);
	temp = substitute_wildcard(temp, wildcard, i);
	return (temp);
}
