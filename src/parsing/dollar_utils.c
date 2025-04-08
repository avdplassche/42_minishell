
#include "minishell.h"

void	init_dollar_alloc(t_mini *mini)
{
	mini->alloc.line_out = NULL;
	mini->alloc.prefix = NULL;
	mini->alloc.suffix = NULL;
	mini->alloc.temp = NULL;
	mini->alloc.var_name = NULL;
	mini->alloc.var_env = NULL;
	mini->alloc.var_value = NULL;
}

/** If the $ sign is followed by an invalid variable,
 * this function delete the $VARIABLE
 * @param temp1 the string to elag
 * @param quote the quotes state
 * @param i where the suppression is needed
 * @return temp1  without $VARIABLE
 */
char	*empty_expand(char *temp1, t_quote q, int i)
{
	char	*temp2;
	char	*dest;
	char	*suffix;

	temp2 = ft_substr(temp1, 0, i);
	while (temp1[++i])
		if (temp1[i] == ' ' || (temp1[i] == 34 && !q.dbl)
			|| (temp1[i] == 39 && !q.sgl))
			break ;
	suffix = ft_substr(temp1, i, ft_strlen(temp1));
	dest = ft_strjoin(temp2, suffix);
	free(temp2);
	free(suffix);
	return (dest);
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
