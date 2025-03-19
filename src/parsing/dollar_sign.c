
#include "minishell.h"


/** If the $ sign is followed by an invalid variable, this function delete the $VARIABLE
 * @param temp1 the string to elag
 * @param quote the quotes state
 * @param i where the suppression is needed
 * @return temp1  without $VARIABLE
 */
char	*empty_expand(char *temp1, t_quote q, int i)
{
	char	*temp2;
	char	*dest;

	temp2 = ft_substr(temp1, 0, i);
	while (temp1[++i])
		if (temp1[i] == ' ' || (temp1[i] == 34 && !q.dbl)
			|| (temp1[i] == 39 && !q.sgl))
			break ;
	dest = ft_strjoin(temp2, ft_substr(temp1, i, ft_strlen(temp1)));
	free(temp2);
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

/** Cut the var name out of the envp line and return it into quote
 * @param mini t_mini containing envp to trim
 * @param index index of envp where is stored the variable
 * Example : USER=alvan-de will return "alvan-de"
 */
char	*trim_var_name(t_mini *mini, int index)
{
	int		i;
	int		j;
	char	*trimmed_str;

	i = 0;
	j = 0;
	while (mini->envp[index][i] && mini->envp[index][i] != '=')
		i++;
	while (mini->envp[index][++i])
		j++;
	trimmed_str = enquote_str(ft_substr(mini->envp[index], i - j, j), 34);
		//malloc protection (malloc in enquote_str)
	return (trimmed_str);
}

/** Replace $VAR by it's value and return new cleaned string
 * @param mini t_mini struct containind envp
 * @param temp1 string containing $VAR to substitut
 * @param envp_index index where to find the variable (if -1, no existing variable, replace by blank)
 * @return temp2 : a string with the value instead of the variable name
 */
char	*replace_env_variable(t_mini *mini, char *temp1, int envp_index, int sub_index)
{
	char	*temp2;
	char	*dest;
	int		i;
	t_quote	q;

	q.sgl = 0;
	q.dbl = 0;
	i = -1;
	while (++i < sub_index)
		quote_enclosure_handle(temp1[i], &q);
	if (envp_index < 0)
		return (empty_expand(temp1, q, i));
	temp2 = ft_strjoin(ft_substr(temp1, 0, i), trim_var_name(mini, envp_index));
	while (temp1[++i] && temp1[i] != ' ')  //can maybe cause problem because of quotes
	{
		if ((q.dbl && temp1[i] == 39) || is_minishell_punct(temp1[i]))
			break ;
		quote_enclosure_handle(temp1[i], &q);
	}
	dest = ft_strjoin(temp2, ft_substr(temp1, i, ft_strlen(temp1)));
	free(temp2);
	return (dest);
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


char	*replace_variable(t_mini *mini, char *temp, int sub_index, int j)
{
	char	*variable_name;
	int		envp_index;
	char	*dest;

	variable_name = ft_substr(temp, sub_index + 1, j);
	envp_index = get_envp_index(mini, ft_strjoin(variable_name, "="));
	free(variable_name);
	dest = replace_env_variable(mini, temp, envp_index, sub_index);
	return (dest);
}


char	*replace_env_return_value(t_mini *mini, char *temp1, int i)
{
	char	*dest;
	char	*temp2;
	int		len;

	len = ft_strlen(temp1);
	dest = ft_substr(temp1, 0, i);
	temp2 = ft_strjoin(dest, ft_itoa(mini->last_return));
	free(dest);
	dest = ft_strjoin(temp2, ft_substr(temp1, i + 2, len - i));
	free(temp1);
	free(temp2);
	return (dest);
}

/** Used to change every dollar sign to elements of env variable
 * @param mini t_mini struct where envp is stored
 * @param temp the string to change dollar sign if needed
 * @return errors
*/
char	*translate_dollar_sign(t_mini *mini, char *temp, int sub_index)
{
	int		i;
	int		j;
	t_quote	q;
	char	*dest;

	j = 0;
	q.sgl = 0;
	q.dbl = 0;
	i = -1;
	while (++i < sub_index)
		quote_enclosure_handle(temp[i], &q);
	if (temp[i + 1] == '?')
		return (replace_env_return_value(mini, temp, i));
	while (temp[++i])
	{
		if ((!q.sgl && (is_quote(temp[i]) || temp[i] == ' '))
			|| (q.dbl && (temp[i] == ' ' || temp[i] == 34))
			|| (!q.sgl && is_minishell_punct(temp[i])))
			break ;
		j++;
		quote_enclosure_handle(temp[i], &q);
	}
	dest = replace_variable(mini, temp, sub_index, j);
	free(temp);
	return (dest);
}

/** Index where a sub is needed
 * @param temp the string to scan
 * @return index where to sub
 * @return -1 no need
*/
int	need_dollar_substitution(char *temp)
{
	int		i;
	t_quote	q;

	if (!(contain_char(temp, '$')))
		return (-1);
	q.sgl = 0;
	q.dbl = 0;
	i = -1;
	while (temp[++i])
	{
		quote_enclosure_handle(temp[i], &q);
		if (temp[i] == '$' && (!q.sgl))
			if (temp[i + 1] && temp[i + 1] != ' ' && !(is_quote(temp[i + 1])))
				return (i);
	}
	return (-1);
}

