
#include "minishell.h"

/** If the $ sign is followed by an invalid variable,
 * this function delete the $VARIABLE
 * @param temp1 the string to elag
 * @param quote the quotes state
 * @param i where the suppression is needed
 * @return temp1  without $VARIABLE
 */
char	*empty_expand(char *line, t_quote q, int i)
{
	char	*prefix;
	char	*line_out;
	char	*suffix;

	prefix = ft_substr(line, 0, i);
	while (line[++i])
		if (line[i] == ' ' || (line[i] == 34 && !q.dbl)
			|| (line[i] == 39 && !q.sgl))
			break ;
	suffix = ft_substr(line, i, ft_strlen(line));
	line_out = ft_strjoin(prefix, suffix);
	free(prefix);
	free(suffix);
	return (line_out);
}

int	is_minishell_punct(char c)
{
	if (c == '!' || ('#' <= c && c <= '&')
		|| ('(' <= c && c <= '/')
		|| c == ':' || c == ';' || c == '='
		|| c == '?' || c == '@' || c == '['
		|| c == ']' || c == '^' || c == '_'
		|| c == '{' || c == '}' || c == '~')
		return (1);
	return (0);
}

/** Get the envp index containing the variable
 * @param mini t_mini struct where envp is stored
 * @param variable the variable name, followed by '='
 * @return errors
*/
int	get_envp_index(t_mini *mini, char *variable)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	len = ft_strlen(variable);
	while (mini->envp[i])
	{
		j = 0;
		k = -1;
		while (variable[++k])
			if (mini->envp[i][j++] != variable[k] && variable[k])
				break ;
		if (k == len)
			return (i);
		i++;
	}
	return (-1);
}
