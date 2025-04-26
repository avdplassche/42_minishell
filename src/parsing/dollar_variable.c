/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:25:56 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/26 12:20:30 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

char	*sub_env_variable(t_mini *mini, char *line, t_alloc *s, int i)
{
	char	*suffix;
	char	*line_out;

	while (line[++i] && line[i] != ' ')
	{
		if ((s->q.dbl && (is_quote(line[i]) || is_minishell_punct(line[i])|| line[i] == '*')))
			break ;
		if (!s->q.dbl && (is_minishell_punct(line[i]) || line[i] == '*'))
			break ;
		quote_enclosure_handle(line[i], &s->q);
	}
	suffix = ft_substr(line, i, ft_strlen(line) - i);
	str_malloc_check(mini, suffix);
	line_out = ft_strjoin(s->prefix, suffix);
	if (!line_out)
	{
		free(suffix);
		exit_minishell(mini);
	}
	free(s->prefix);
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
	int		i;

	init_quotes(&s.q);
	i = -1;
	while (++i < sub_i)
		quote_enclosure_handle(line[i], &s.q);
	if (envp_i < 0)
		return (empty_expand(mini, line, s.q, i));
	s.var_name = trim_var_name(mini, envp_i);
	s.temp = ft_substr(line, 0, i);
	if (!s.temp)
	{
		free(s.var_name);
		exit_minishell(mini);
	}
	s.prefix = ft_strjoin(s.temp, s.var_name);
	free(s.var_name);
	free(s.temp);
	str_malloc_check(mini, s.prefix);
	s.line_out = sub_env_variable(mini, line, &s, i);
	return (s.line_out);
}
