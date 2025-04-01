
#include "minishell.h"

void	get_prefix(t_wildcard *w, char *temp, int i)
{
	while (i >= 0 && temp[i] != '/')
		i--;
	if (w->current)
		return ;
	else if (i == 0)
		w->prefix = ft_strdup(w->dirname);
	else
		w->prefix = ft_strjoin(w->dirname, "/");
}

void	get_suffix(t_wildcard *w, char *temp, int i)
{
	int	len;

	len = ft_strlen(temp) - 1;
	while (i <= len && temp[i] != '/')
		i++;
	if (temp[len] == '/')
		w->suffix = ft_strdup("/");
	else if (temp[i] == '/' && i < len)
		w->suffix = ft_substr(temp, i, len - i + 1);
}

void	change_affixes(char **file_list, char *temp1, t_wildcard *w, int i)
{
	int		len;
	int		j;
	char	*temp2;

	temp2 = NULL;
	j = -1;
	len = double_array_len(file_list);

	get_prefix(w, temp1, i);
	get_suffix(w, temp1, i);
	while (++j < len)
	{
		temp2 = ft_strdup(file_list[j]);
		free(file_list[j]);
		file_list[j] = join_three_strings(w->prefix, temp2, w->suffix);
		free(temp2);
	}
}