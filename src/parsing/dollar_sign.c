
#include "../../includes/minishell.h"

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
	t_quote	quote;

	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (++i < sub_index)
		quote_enclosure_handle(temp1[i], &quote);
	if (envp_index < 0)
	{
		temp2 = ft_substr(temp1, 0, i);
		while (temp1[++i])
			if (temp1[i] == ' ' || (temp1[i] == 34 && !quote.dbl))
				break ;
		dest = ft_strjoin(temp2, ft_substr(temp1, i, ft_strlen(temp1)));
		return (dest);
	}
	temp2 = ft_strjoin(ft_substr(temp1, 0, i), trim_var_name(mini, envp_index));
	while (temp1[++i] && temp1[i] != ' ')  //can maybe cause problem because of quotes
	{
		if (quote.dbl == 1 && temp1[i] == 39)
			break ;
		quote_enclosure_handle(temp1[i], &quote);
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
	printf("Before replace : temp = %s env = %d\n", temp, envp_index);
	dest = replace_env_variable(mini, temp, envp_index, sub_index);
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
	t_quote	quote;
	char	*dest;

	j = 0;
	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (++i < sub_index)
		quote_enclosure_handle(temp[i], &quote);
	while (temp[++i])
	{
		quote_enclosure_handle(temp[i], &quote);
		if ((!quote.sgl && (is_quote(temp[i]) || temp[i] == ' '))
			|| (quote.dbl && (temp[i] == ' ' || temp[i] == 34)))
			break ;
		j++;
	}
	dest = replace_variable(mini, temp, sub_index, j);
	free(temp);
	return (dest);
}

/** Index where a sub is needed
 * @param str the string to scan
 * @return index where to sub
 * @return -1 no need
*/
int	need_dollar_substitution(char *str)
{
	int		i;
	t_quote	quote;

	if (!(contain_char(str, '$')))
		return (-1);
	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (str[++i])
	{
		quote_enclosure_handle(str[i], &quote);
		if (str[i] == '$' && (!quote.sgl || (quote.sgl && quote.dbl && last_quote(str, i) == 's')))
			return (i);
	}
	return (-1);
}

