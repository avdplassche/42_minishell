#include "minishell.h"

static int	ft_strcmp_ascii(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] == '=' && s2[i] != '=' && s2[i] != '\0')
		return (-1);
	else if (s2[i] == '=' && s1[i] != '=' && s1[i] != '\0')
		return (1);
	else if (s1[i] == '\0' && s2[i] != '=' && s2[i])
		return (-1);
	else if (s2[i] == '\0' && s1[i] != '=' && s1[i])
		return (1);
	return (0);
}

void	sort_ascii_array(char	**string_array, int len)
{
	int		i;
	int		j;
	char	*temp;
	
	while (len > 0)
	{
		i = 0;
		j = 1;
		while (j < len)
		{
			if (ft_strcmp_ascii(string_array[i], string_array[j]) > 0)
			{
				temp = string_array[i];
				string_array[i] = string_array[j];
				string_array[j] = temp;
			}
			i++;
			j++;
		}
		len--;
	}
}
