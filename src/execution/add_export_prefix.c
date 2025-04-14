
#include "minishell.h"

char	**add_export_prefix(char **string_array)
{
	char	*prefix;
	char	**temp;
	int		i;

	prefix = "declare -x ";
	i = 0;
	while (string_array && string_array[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (string_array[i])
	{
		if (ft_strncmp(prefix, string_array[i], ft_strlen(prefix)) == 0)
			temp[i] = ft_strdup(string_array[i]);
		else
			temp[i] = ft_strjoin(prefix, string_array[i]);
		if (!temp[i])
		{
			while (--i >= 0)
				free(temp[i]);
			free(temp);
			return NULL;
		}
		i++;
	}
	temp[i] = NULL;
	i = 0;
	free(string_array);
	return (temp);
}
