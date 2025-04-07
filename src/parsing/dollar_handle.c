
#include "minishell.h"

char	*replace_variable(t_mini *mini, char *temp, int sub_index, int j)
{
	char	*variable_name;
	int		envp_index;
	char	*dest;
	char	*temp2;

	// DEBUG("Replace variable\n Temp : %s\n Sub index : %d\n j = %d\n\n", temp, sub_index, j);
	variable_name = ft_substr(temp, sub_index + 1, j);
	temp2 = ft_strjoin(variable_name, "=");
	envp_index = get_envp_index(mini, temp2);
	free(temp2);
	free(variable_name);
	dest = get_env_variable(mini, temp, envp_index, sub_index);
	return (dest);
}

char	*replace_env_return_value(t_mini *mini, int i)
{
char	*dest;
	char	*temp2;
	int		len;
	char	*suffix;

	DEBUG("Replace env return value\n mini->line : %s\n i = %d\n\n", mini->line, i);
	// dest = malloc(sizeof(char) * (i + get_int_len(mini->last_return * ft_strlen(suffix)));
	len = ft_strlen(mini->line);
	dest = ft_substr(mini->line, 0, i);
	suffix = ft_itoa(mini->last_return);
	temp2 = ft_strjoin(dest, suffix);
	free(suffix);
	free(dest);
	suffix = ft_substr(mini->line, i + 2, len - i);
	dest = ft_strjoin(temp2, suffix);
	free(suffix);
	free(mini->line);
	free(temp2);
	return (dest);
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
	line_out = replace_variable(mini, mini->line, sub_index, j);
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
