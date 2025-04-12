
#include "minishell.h"

char	**add_export_prefix(char **string_array)
{
	char	*prefix;
	int		i;

	prefix = "declare -x ";
	i = 0;
	while (string_array[i])
	{
		if (ft_strncmp(prefix, string_array[i], ft_strlen(prefix)) == 0)
		{
			i++;
		}
		else
		{
			string_array[i] = ft_strjoin(prefix, string_array[i]);
			if (!string_array[i])
			{
				return (NULL);
			}
			i++;
		}
	}
	return (string_array);
}
