/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:25:43 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/24 16:00:50 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** If the $ sign is followed by an invalid variable,
 * this function delete the $VARIABLE
 * @param temp1 the string to elag
 * @param quote the quotes state
 * @param i where the suppression is needed
 * @return temp1  without $VARIABLE
 */
char	*empty_expand(t_mini *mini, char *line, t_quote q, int i)
{
	t_alloc	s;

	s.prefix = ft_substr(line, 0, i);
	str_malloc_check(mini, s.prefix);
	while (line[++i])
		if (line[i] == ' ' || (line[i] == 34 && !q.dbl)
			|| (line[i] == 39 && !q.sgl) || is_minishell_punct(line[i]) || line[i] == '*')
			break ;
	if (line[i] == '*' && line[i - 1] == '$')
		i++;
	s.suffix = ft_substr(line, i, ft_strlen(line));
	if (!s.suffix)
	{
		free(s.prefix);
		exit_minishell(mini, mini->cmd);
	}
	s.line_out = ft_strjoin(s.prefix, s.suffix);
	free(s.prefix);
	free(s.suffix);
	str_malloc_check(mini, s.line_out);
	return (s.line_out);
}

int	is_minishell_punct(char c)
{
	if (('!' <= c && c <= ')')
		|| ('+' <= c && c <= '/')
		|| (':' <= c && c <= '@')
		|| ('[' <= c && c <= '^')
		|| ('{' <= c && c <= '~'))
		return (1);
	return (0);
}

/** Get the envp index containing the variable
 * @param mini t_mini struct where envp is stored
 * @param variable the variable name, followed by '='
 * @return errors
*/
int	get_envp_index(t_mini *mini, char *variable)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	len = ft_strlen(variable);
	while (mini->envp[i])
	{
		j = 0;
		k = -1;
		while (variable[++k])
			if (mini->envp[i][j++] != variable[k] && variable[k])
				break ;
		if (k == len)
			return (i);
		i++;
	}
	return (-1);
}
