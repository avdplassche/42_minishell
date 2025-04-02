
#include "minishell.h"

char	*replace_variable(t_mini *mini, char *temp, int sub_index, int j)
{
	char	*variable_name;
	int		envp_index;
	char	*dest;
	char	*temp2;

	variable_name = ft_substr(temp, sub_index + 1, j);
	temp2 = ft_strjoin(variable_name, "=");
	envp_index = get_envp_index(mini, temp2);
	free(temp2);
	free(variable_name);
	dest = get_env_variable(mini, temp, envp_index, sub_index);
	return (dest);
}

char	*replace_env_return_value(t_mini *mini, char *temp1, int i)
{
	char	*dest;
	char	*temp2;
	int		len;
	char	*suffix;

	len = ft_strlen(temp1);
	dest = ft_substr(temp1, 0, i);
	suffix = ft_itoa(mini->last_return);
	temp2 = ft_strjoin(dest, suffix);
	free(suffix);
	free(dest);
	suffix = ft_substr(temp1, i + 2, len - i);
	dest = ft_strjoin(temp2, suffix);
	free(suffix);
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

char	*dollar_handle(t_mini *mini, char *temp)
{
	int	i;

	i = need_dollar_substitution(temp);
	while (i > -1)
	{
		temp = translate_dollar_sign(mini, temp, i);
		i = need_dollar_substitution(temp);
	}
	return (temp);
}
