
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
/** Substitute "$?"
 */
char	*replace_env_return_value(t_mini *mini, int i)
{
	t_alloc	*str;
	int		len;
	int		v_len;

	str = &mini->alloc;
	len = ft_strlen(mini->line);
	v_len = get_int_len(mini->last_return);
	str->line_out = malloc(sizeof(char) * (len + v_len - 1));
	if (!str->line_out)
		exit_minishell(mini, mini->cmd);
	ft_strlcpy(str->line_out, mini->line, i + 1);
	str->number = ft_itoa(mini->last_return);
	if (!str->number)
		exit_minishell(mini, mini->cmd);
	ft_strlcat(str->line_out, str->number, i + 1 + v_len);
	if (len > i + 2)
	{
		str->suffix = ft_substr(mini->line, i + 2, len - v_len - i);
		if (!str->suffix)
			exit_minishell(mini, mini->cmd);
		ft_strlcat(str->line_out, str->suffix, len + v_len - 1);
	}
	free_string_ptr(mini->line);
	mini->line = ft_strdup(str->line_out);
	if (!mini->line)
		exit_minishell(mini, mini->cmd);
	return (mini->line);
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
	t_alloc	*str;

	// DEBUG("Translate dollar sign\n mini->line : %s\n Sub index : %d\n\n", mini->line, sub_index);
	i = -1;
	j = 0;
	str = &mini->alloc;
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
	str->line_out = replace_variable(mini, sub_index, j);
	free(mini->line);
	mini->line = ft_strdup(str->line_out);
	return (mini->line);
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
		init_dollar_alloc(mini);
		mini->line = translate_dollar_sign(mini, i);
		i = need_dollar_substitution(mini);
		free_dollar_alloc(mini);
	}
	return (mini->line);
}
