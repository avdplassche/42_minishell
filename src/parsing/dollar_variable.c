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
	char	*var_value;

	// DEBUG("Trim var name : \nIndex : %d\n\n", index);
	i = 0;
	j = 0;
	while (mini->envp[index][i] && mini->envp[index][i] != '=')
		i++;
	while (mini->envp[index][++i])
		j++;
	var_value = ft_substr(mini->envp[index], i - j, j);
	if (!var_value)
		exit_minishell(mini, mini->cmd);
	return (var_value);
}

char	*sub_env_variable(t_mini *mini, char *prefix, int i, t_quote *q)
{
	char	*suffix;
	char	*line_out;

	// DEBUG("Sub Env Variable\n Temp : %s\nprefix : %s\n  i : %d\n\n", temp, prefix, i);
	while (mini->line[++i] && mini->line[i] != ' ')
	{
		if ((q->dbl && (mini->line[i] == 34 || mini->line[i] == 39 || is_minishell_punct(mini->line[i]))))
			break ;
		quote_enclosure_handle(mini->line[i], q);
	}
	suffix = ft_substr(mini->line, i, ft_strlen(mini->line) - i);
	if (!suffix)
		exit_minishell(mini, mini->cmd);
	line_out = ft_strjoin(prefix, suffix);
	if (!line_out)
	{
		free(suffix);
		exit_minishell(mini, mini->cmd);
	}
	free(suffix);
	return (line_out);
}

/** Replace $VAR by it's value and return new cleaned string
 * @param mini t_mini struct containind envp
 * @param temp1 string containing $VAR to substitut
 * @param envp_index index where to find the variable
 * (if -1, no existing variable, replace by blank)
 * @return temp2 : a string with the value instead of the variable name
 */
char	*get_env_variable(t_mini *mini, int envp_i, int sub_i)
{
	char	*prefix;
	char	*line_out;
	char	*temp;
	char	*var_name;
	int		i;
	t_quote	q;

	// DEBUG("Get Env Variable\n Line: %s\nenvp_i : %d\n  sub_i : %d\n", mini->line, envp_i, sub_i);
	init_quotes(&q);
	i = -1;
	while (++i < sub_i)
		quote_enclosure_handle(mini->line[i], &q);
	if (envp_i < 0)
		return (empty_expand(mini->line, q, i));
	var_name = trim_var_name(mini, envp_i);
	temp = ft_substr(mini->line, 0, i);
	if (!temp)
		exit_minishell(mini, mini->cmd);
	prefix = ft_strjoin(temp, var_name);
	if (!prefix)
		exit_minishell(mini, mini->cmd);
	free(var_name);
	free(temp);
	line_out = sub_env_variable(mini, prefix, i, &q);
	free(prefix);
	return (line_out);
}
