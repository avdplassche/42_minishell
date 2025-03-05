
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
char	*replace_env_variable(t_mini *mini, char *temp1, int envp_index)
{
	char	*temp2;
	char	*dest;
	int		i;
	t_quote	quote;

	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (temp1[++i] && temp1[i] != '$' && (quote.sgl == 0 || (quote.sgl == 1 && quote.dbl == 1)))
		quote_enclosure_handle(temp1[i], &quote);
	// if (envp_index < 0)
	temp2 = ft_strjoin(ft_substr(temp1, 0, i), trim_var_name(mini, envp_index));
	while (temp1[++i] && temp1[i] != ' ')  //can maybe cause problem because of quotes
		quote_enclosure_handle(temp1[i], &quote);
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
		k = 0;
		while (variable[k])
			if (mini->envp[i][j++] != variable[k++])
				break ;
		if (k == len)
			return (i);
		i++;
	}
	return (-1);
}

/** Used to change every dollar sign to elements of env variable
 * @param mini t_mini struct where envp is stored
 * @param temp the string to change dollar sign if needed
 * @return errors
*/
char	*translate_dollar_sign(t_mini *mini, char *temp)
{
	int		i;
	int		j;
	t_quote	quote;
	char	*variable_name;
	int		envp_index;

	printf("Variable : %s\n", temp);
	j = 0;
	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (temp[++i] && temp[i] != '$' && quote.sgl == 0)
		quote_enclosure_handle(temp[i], &quote);
	printf("i = %d\n", i);
	while (temp[++i] && temp[i] != ' ' && temp[i] != 34)
		j++;
	variable_name = ft_substr(temp, i - j, j + 1);
	variable_name[j] = '=';
	variable_name[j + 1] = '\0';
	printf("Variable : %s\n", variable_name);
	envp_index = get_envp_index(mini, variable_name);
	free(variable_name);
	variable_name = replace_env_variable(mini, temp, envp_index);	// example : $USER becomes "alvan-de", not alvan-de
	free(temp);
	return (variable_name);
}

/** Do the string needs a dollar sign substitution ?
 * @param str the string to scan
 * @return 1 yes
 * @return 0 no
*/
int	dollar_sub_needed(char *str)
{
	int		i;
	t_quote	quote;

	if (!(contain_char(str, '$')))
		return (0);
	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && (quote.sgl == 0 || (quote.sgl && quote.dbl)))
			return (printf("\n"), 1);
		quote_enclosure_handle(str[i], &quote);
	}
	return (0);
}

