
#include "minishell.h"

void	tokenize_wildcard(t_wildcard *w, char *temp, int start)
{
	int		len;

	len = start;
	while (start >= 0 && temp[start] != '/' && temp[start] != ' ')
		start--;
	start ++;
	while (temp[len] && temp[len] != '/')
		len++;
	if (temp[len] == '/')
		len ++;
	w->token = ft_substr(temp, start, len - start);
}

int	is_last_asterisk(char *token, int i)
{
	while (token[i++])
		if (token[i] == '*')
			return (0);
	return (1);
}

char	*crop_args(char *temp)
{
	char	*dest;
	int		i;

	if (!contain_char(temp, ' '))
		return (temp);
	i = 0;
	while (temp [i] != ' ')
		i++;
	i++;
	dest = ft_substr(temp, i, ft_strlen(temp) - i);
	return (dest);
}

char	*crop_command(char *temp)
{
	int		i;
	char	*dest;

	i = 0;
	if (!contain_char(temp, ' '))
		return (temp);
	while (temp[i] && temp[i] != ' ')
		i++;
	DEBUG("TEMP = %s\n\n", temp);
	dest = ft_substr(temp, 0, i + 1);
	free(temp);
	return(dest);
}

int	get_new_index(char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != '*')
		i++;
	return (i);
}
