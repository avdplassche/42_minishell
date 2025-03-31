
#include "minishell.h"


void	init_wildcard_struct(t_wildcard *w)
{
	w->dirname = NULL;
	w->token = NULL;
	w->s_dir = NULL;
	w->prefix = NULL;
	w->suffix = NULL;
	w->current = false;
}


char	*get_sub_token(char **file_list, int file_amount)
{
	int		len;
	char	*str;

	len = file_amount - 2;
	while (len >= 0)
	{
		append_space_to_string(&file_list[len]);
		len--;
	}
	str = join_n_strings(file_list, file_amount);
	free(file_list);
	return (str);
}

char	*substitute_wildcard(char *temp, int i)
{
	t_wildcard		w;
	DIR				*folder;
	char			**file_list;
	int				file_amount;
	char			*dest;
	char			*temp2;

	temp2 = crop_args(temp);
	i = get_new_index(temp2);
	folder = NULL;
	init_wildcard_struct(&w);
	set_wildcard_directory(&w, temp2, i);
	tokenize_wildcard(&w, temp2, i);
	file_amount = count_valid_files(folder, w);
	if (!file_amount)
		return (free_wildcard_struct(&w), temp);
	file_list = fill_file_list(folder, w, file_amount);
	sort_array(file_list, double_array_len(file_list));
	change_affixes(file_list, temp2, &w, i);
	temp = crop_command(temp);
	dest = ft_strjoin (temp, get_sub_token(file_list, file_amount));
	closedir(folder);
	// free_wildcard_struct(&w);  /* CHECK, maybe put it in change affizes*/
	free(temp);
	free_string_array(file_list);
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
		}
	}
	return (-1);
}

/**Go through the command and do all the substitutions
 */
char	*wildcard_handle(char *temp)
{
	int		i;

	i = need_wildcard_substitution(temp);
	if (i == -1)
		return (temp);
	if (i != -1)
	{
		temp = substitute_wildcard(temp, i);
		i = need_wildcard_substitution(temp);
	}
	return (temp);
}
