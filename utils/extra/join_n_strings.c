
#include "minishell.h"

char	*join_n_strings(char **file_list, int n)
{
	char	*str;
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 1;
	if (n == 1)
		return (file_list[0]);
	str = ft_strjoin(file_list[i], file_list[j++]);;
	while (j < n)
	{
		temp = ft_strjoin(str, file_list[j]);
		j++;
		free(str);
		str = ft_strdup(temp);
		free(temp);
	}
	return (str);
}