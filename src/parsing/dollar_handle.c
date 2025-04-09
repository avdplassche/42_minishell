
#include "minishell.h"

char	*replace_variable(t_mini *mini, char *line, int sub_index, int j)
{
	char	*var_name;
	char	*var_env;
	int		envp_index;
	char	*line_out;


	// DEBUG("Replace variable\n Temp : %s\n Sub index : %d\n j = %d\n\n", temp, sub_index, j);
	var_name = ft_substr(line, sub_index + 1, j);
	if (!var_name)
		exit_minishell(mini, mini->cmd);
	var_env = ft_strjoin(var_name, "=");
	if (!var_env)
		exit_minishell(mini, mini->cmd);
	envp_index = get_envp_index(mini, var_env);
	free(var_env);
	free(var_name);
	line_out = get_env_variable(mini, line, envp_index, sub_index);
	return (line_out);
}
/** Substitute "$?"
 */
char	*replace_env_return_value(t_mini *mini, char *line, int i)
{
	char	*line_out;
	char	*number;
	char	*suffix;
	int		len;
	int		v_len;

	suffix = NULL;
	len = ft_strlen(line);
	v_len = get_int_len(mini->last_return);
	line_out = malloc(sizeof(char) * (len + v_len - 1));
	if (!line_out)
		exit_minishell(mini, mini->cmd);
	ft_strlcpy(line_out, line, i + 1);
	number = ft_itoa(mini->last_return);
	if (!number)
		exit_minishell(mini, mini->cmd);
	ft_strlcat(line_out, number, i + 1 + v_len);
	free_string_ptr(number);
	if (len > i + 2)
	{
		suffix = ft_substr(line, i + 2, len - v_len - i);
		if (!suffix)
			exit_minishell(mini, mini->cmd);
		ft_strlcat(line_out, suffix, len + v_len - 1);
		free(suffix);
	}
	free_string_ptr(line);
	line = ft_strdup(line_out);
	if (!line)
		exit_minishell(mini, mini->cmd);
	free_string_ptr(line_out);
	return (line);
}

/** Used to change every dollar sign to elements of env variable
 * @param mini t_mini struct where envp is stored
 * @param temp the string to change dollar sign if needed
 * @return errors
*/
static char	*translate_dollar_sign(t_mini *mini, char *line, int sub_index)
{
	int		i;
	int		j;
	t_quote	q;
	char	*line_out;

	// DEBUG("Translate dollar sign\n line : %s\n Sub index : %d\n\n", line, sub_index);
	i = -1;
	j = 0;
	init_quotes(&q);
	while (++i < sub_index)
		quote_enclosure_handle(line[i], &q);
	if (line[i + 1] == '?')
		return (replace_env_return_value(mini, line, i));
	while (line[++i])
	{
		if ((!q.sgl && (is_quote(line[i]) || line[i] == ' '))
			|| (q.dbl && (line[i] == ' ' || line[i] == 34))
			|| (!q.sgl && is_minishell_punct(line[i])))
			break ;
		j++;
		quote_enclosure_handle(line[i], &q);
	}
	line_out = replace_variable(mini, line, sub_index, j);
	free(line);
	return (line_out);
}

/** Index where a sub is needed
 * @param temp the string to scan
 * @return index where to sub
 * @return -1 no need
*/
static int	need_dollar_substitution(char *line)
{
	int		i;
	t_quote	q;

	DEBUG("Need dollar substitution\n line : %s\n\n", line);
	if (!(contain_char(line, '$')))
		return (-1);
	init_quotes(&q);
	i = -1;
	while (line[++i])
	{
		quote_enclosure_handle(line[i], &q);
		if (line[i] == '$' && (!q.sgl))
			if (line[i + 1] && line[i + 1] != ' ' && !(is_quote(line[i + 1])))
				return (i);
	}
	return (-1);
}

char	*dollar_handle(t_mini *mini, char *line)
{
	int	i;
	
	i = need_dollar_substitution(line);
	DEBUG("Dollar handle\n line = %s\ni = %d\n", line, i);
	while (i > -1)
	{
		line = translate_dollar_sign(mini, line, i);
		i = need_dollar_substitution(line);
	}
	return (line);
}
