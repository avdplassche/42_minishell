/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:25:22 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/24 01:14:33 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_variable(t_mini *mini, char *line, int sub_index, int j)
{
	char	*var_name;
	char	*var_env;
	int		envp_index;
	char	*line_out;

	var_name = ft_substr(line, sub_index + 1, j);
	str_malloc_check(mini, var_name);
	var_env = ft_strjoin(var_name, "=");
	if (!var_env)
	{
		free(var_name);
		exit_minishell(mini, mini->cmd);
	}
	envp_index = get_envp_index(mini, var_env);
	free(var_env);
	free(var_name);
	line_out = get_env_variable(mini, line, envp_index, sub_index);
	return (line_out);
}

/** Substitute "$?"
 */
char	*replace_env_return_value(t_mini *mini, char *temp1, int i)
{
	t_alloc	s;
	int		len;

	len = ft_strlen(temp1);
	s.line_out = ft_substr(temp1, 0, i);
	str_malloc_check(mini, s.line_out);
	s.number = ft_itoa(mini->last_return);
	if (!s.number)
	{
		free(s.line_out);
		exit_minishell(mini, mini->cmd);
	}
	s.suffix = ft_strjoin(s.line_out, s.number);
	free(s.number);
	free(s.line_out);
	str_malloc_check(mini, s.suffix);
	s.number = ft_substr(temp1, i + 2, len - i);
	str_malloc_check(mini, s.number);
	s.line_out = ft_strjoin(s.suffix, s.number);
	free(s.number);
	free(temp1);
	free(s.suffix);
	str_malloc_check(mini, s.line_out);
	return (s.line_out);
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
	free_string_ptr(&line);
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

	if (!(contain_char(line, '$')))
		return (-1);
	init_quotes(&q);
	i = -1;
	while (line[++i])
	{
		quote_enclosure_handle(line[i], &q);
		if (line[i] == '$' && (!q.sgl))
			if (line[i + 1] && line[i + 1] != ' ' && !(is_quote(line[i + 1]))
				&& !ft_isdigit(line[i + 1]))
				return (i);
	}
	return (-1);
}

char	*dollar_handle(t_mini *mini, char *line)
{
	int	i;

	i = need_dollar_substitution(line);
	if (i == -1)
		return (line);
	while (i > -1)
	{
		line = translate_dollar_sign(mini, line, i);
		i = need_dollar_substitution(line);
	}
	return (line);
}
