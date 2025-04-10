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

	i = 0;
	j = 0;
	while (mini->envp[index][i] && mini->envp[index][i] != '=')
		i++;
	while (mini->envp[index][++i])
		j++;
	var_value = ft_substr(mini->envp[index], i - j, j);
	str_malloc_check(mini, var_value);
	return (var_value);
}

char	*sub_env_variable(t_mini *mini, char *line, char *prefix, int i, t_quote *q)
{
	char	*suffix;
	char	*line_out;

	while (line[++i] && line[i] != ' ')
	{
		if ((q->dbl && (line[i] == 34 || line[i] == 39 || is_minishell_punct(line[i]))))
			break ;
		if (!q->dbl && is_minishell_punct(line[i]))
			break ;
		quote_enclosure_handle(line[i], q);
	}
	suffix = ft_substr(line, i, ft_strlen(line) - i );
	str_malloc_check(mini, suffix);
	line_out = ft_strjoin(prefix, suffix);
	if (!line_out)
	{
		free(suffix);
		exit_minishell(mini, mini->cmd);
	}
	free(prefix);
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
char	*get_env_variable(t_mini *mini, char *line, int envp_i, int sub_i)
{
	t_alloc	s;
	t_quote	q;
	int		i;

	init_quotes(&q);
	i = -1;
	while (++i < sub_i)
		quote_enclosure_handle(line[i], &q);
	if (envp_i < 0)
		return (empty_expand(mini, line, q, i));
	s.var_name = trim_var_name(mini, envp_i);
	s.temp = ft_substr(line, 0, i);
	if (!s.temp)
	{
		free(s.var_name);
		exit_minishell(mini, mini->cmd);
	}
	s.prefix = ft_strjoin(s.temp, s.var_name);
	free(s.var_name);
	free(s.temp);
	str_malloc_check(mini, s.prefix);
	s.line_out = sub_env_variable(mini, line, s.prefix, i, &q);
	return (s.line_out);
}
