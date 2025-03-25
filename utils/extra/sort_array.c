#include "minishell.h"

void	sort_array(char **filename, int len)
{
	int		i;
	int		j;
	char	*temp;

	if (len <= 1)
		return ;
	while (len > 0)
	{
		i = 0;
		j = 1;
		while (j < len)
		{
			if (ft_strcmp_alpha(filename[i], filename[j]) > 0)
			{
				temp = filename[i];
				filename[i] = filename[j];
				filename[j] = temp;
			}
			i++;
			j++;
		}
		len --;
	}
}
