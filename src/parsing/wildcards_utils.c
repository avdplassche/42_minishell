
#include "minishell.h"

void	tokenize_wildcard(t_mini *mini, t_wildcard *w, char *temp, int start)
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
	str_malloc_wildcard_check(mini, w, w->token);
}

int	is_last_asterisk(char *token, int i)
{
	while (token[i++])
		if (token[i] == '*')
			return (0);
	return (1);
}

void	set_wildcard(t_mini *mini, char *line, t_wildcard *w)
{
	int		i;

	if (!contain_char(line, ' '))
	{
		w->wildcard = ft_strdup(line);
		str_malloc_check(mini, w->wildcard);
		return ;
	}
	i = 0;
	while (line [i] != ' ')
		i++;
	i++;
	w->wildcard = ft_substr(line, i, ft_strlen(line) - i);
	str_malloc_check(mini, w->wildcard);
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
	dest = ft_substr(temp, 0, i + 1);
	free(temp);
	return (dest);
}

int	get_new_index(char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != '*')
		i++;
	return (i);
}
