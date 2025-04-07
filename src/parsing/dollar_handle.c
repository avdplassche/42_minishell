
#include "minishell.h"

char	*replace_variable(t_mini *mini, int sub_index, int j)
{
	char	*var_name;
	char	*var_env;
	int		envp_index;
	char	*line_out;


	// DEBUG("Replace variable\n Temp : %s\n Sub index : %d\n j = %d\n\n", temp, sub_index, j);
	var_name = ft_substr(mini->line, sub_index + 1, j);
	if (!var_name)
		exit_minishell(mini, mini->cmd);
	var_env = ft_strjoin(var_name, "=");
	if (!var_env)
		exit_minishell(mini, mini->cmd);
	envp_index = get_envp_index(mini, var_env);
	free(var_env);
	free(var_name);
	line_out = get_env_variable(mini, envp_index, sub_index);
	return (line_out);
}

char	*replace_env_return_value(t_mini *mini, int i)
{
	char	*line_out;
	// char	*temp2;
	int		len;
	int		v_len;
	char	*number;
	char	*suffix = NULL;

	len = ft_strlen(mini->line);
	v_len = get_int_len(mini->last_return);
	line_out = malloc(sizeof(char) * (len + v_len - 1));
	if (!line_out)
		exit_minishell(mini, mini->cmd);
	ft_strlcpy(line_out, mini->line, i + 1);
	number = ft_itoa(mini->last_return);
	ft_strlcat(line_out, number, i + 1 + v_len);
	if (len > i + 2)
	{
		suffix = ft_substr(mini->line, i + 2, len - v_len - i);
		if (!suffix)
			exit_minishell(mini, mini->cmd);
		ft_strlcat(line_out, suffix, len + v_len - 1);
	}

	// line_out = ft_substr(mini->line, 0, i);
	// suffix = ft_itoa(mini->last_return);
	// temp2 = ft_strjoin(line_out, suffix);
	// free(suffix);
	// free(line_out);
	// suffix = ft_substr(mini->line, i + 2, len - i);
	// line_out = ft_strjoin(temp2, suffix);
	// free(suffix);
	// free(temp2);
	free(mini->line);
	return (line_out);
}

/** Used to change every dollar sign to elements of env variable
 * @param mini t_mini struct where envp is stored
 * @param temp the string to change dollar sign if needed
 * @return errors
*/
static char	*translate_dollar_sign(t_mini *mini, int sub_index)
{
	int		i;
	int		j;
	t_quote	q;
	char	*line_out;

	// DEBUG("Translate dollar sign\n mini->line : %s\n Sub index : %d\n\n", mini->line, sub_index);
	i = -1;
	j = 0;
	init_quotes(&q);
	while (++i < sub_index)
		quote_enclosure_handle(mini->line[i], &q);
	if (mini->line[i + 1] == '?')
		return (replace_env_return_value(mini, i));
	while (mini->line[++i])
	{
		if ((!q.sgl && (is_quote(mini->line[i]) || mini->line[i] == ' '))
			|| (q.dbl && (mini->line[i] == ' ' || mini->line[i] == 34))
			|| (!q.sgl && is_minishell_punct(mini->line[i])))
			break ;
		j++;
		quote_enclosure_handle(mini->line[i], &q);
	}
	line_out = replace_variable(mini, sub_index, j);
	free(mini->line);
	return (line_out);
}

/** Index where a sub is needed
 * @param temp the string to scan
 * @return index where to sub
 * @return -1 no need
*/
static int	need_dollar_substitution(t_mini *mini)
{
	int		i;
	t_quote	q;

	// DEBUG("Need dollar substitution\n mini->line : %s\n\n", mini->line);
	if (!(contain_char(mini->line, '$')))
		return (-1);
	init_quotes(&q);
	i = -1;
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &q);
		if (mini->line[i] == '$' && (!q.sgl))
			if (mini->line[i + 1] && mini->line[i + 1] != ' ' && !(is_quote(mini->line[i + 1])))
				return (i);
	}
	return (-1);
}

char	*dollar_handle(t_mini *mini)
{
	int	i;

	i = need_dollar_substitution(mini);
	while (i > -1)
	{
		mini->line = translate_dollar_sign(mini, i);
		i = need_dollar_substitution(mini);
	}
	return (mini->line);
}
