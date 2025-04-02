#include "minishell.h"

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
	trimmed_str = ft_substr(mini->envp[index], i - j, j);
	if (!trimmed_str)
		return (NULL);
	return (trimmed_str);
}

char	*sub_env_variable(char *temp, char *temp2, int i, t_quote *q)
{
	char	*affix;
	char	*dest;

	while (temp[++i] && temp[i] != ' ')
	{
		if ((q->dbl && (temp[i] == 34 || is_minishell_punct(temp[i]))))
			break ;
		quote_enclosure_handle(temp[i], q);
	}
	affix = ft_substr(temp, i, ft_strlen(temp));
	if (!affix)
		return (NULL);
	dest = ft_strjoin(temp2, affix);
	if (!dest)
		return (free(affix), NULL);
	free(affix);
	free(temp2);
	return (dest);
}

/** Replace $VAR by it's value and return new cleaned string
 * @param mini t_mini struct containind envp
 * @param temp1 string containing $VAR to substitut
 * @param envp_index index where to find the variable 
 * (if -1, no existing variable, replace by blank)
 * @return temp2 : a string with the value instead of the variable name
 */
char	*get_env_variable(t_mini *mini, char *temp, int envp_i, int sub_i)
{
	char	*temp2;
	char	*dest;
	char	*var_name;
	int		i;
	t_quote	q;

	q.sgl = 0;
	q.dbl = 0;
	i = -1;
	while (++i < sub_i)
		quote_enclosure_handle(temp[i], &q);
	if (envp_i < 0)
		return (empty_expand(temp, q, i));
	var_name = trim_var_name(mini, envp_i);
	dest = ft_substr(temp, 0, i);
	if (!dest)
		return (NULL);
	temp2 = ft_strjoin(dest, var_name);
	if (!dest)
		return (NULL);
	free(var_name);
	free(dest);
	dest = sub_env_variable(temp, temp2, i, &q);
	return (dest);
}
