
#include "minishell.h"

char	*join_n_strings_wildcards(t_mini *mini, t_wildcard *w)
{
	char	*str;
	int		i;
	int		j;
	char	*temp;
	(void)mini;

	i = 0;
	temp= NULL;
	str = NULL;
	j = 1;
	if (w->file_amount == 1)
		return (w->file_list[0]);
	str = ft_strjoin(w->file_list[i], w->file_list[j++]);;
	while (j < w->file_amount)
	{
		temp = ft_strjoin(str, w->file_list[j]);
		j++;
		free(str);
		str = NULL;
		str = ft_strdup(temp);
		free(temp);
		temp = NULL;
	}
	return (str);
}
