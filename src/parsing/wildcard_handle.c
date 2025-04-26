/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:38:27 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/26 17:06:13 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last_asterisk(char *token, int i)
{
	while (token[i++])
		if (token[i] == '*')
			return (0);
	return (1);
}

/**Tests if a substitution is needed
 */
int	need_wildcard_substitution(char *line)
{
	int		i;
	t_quote	q;

	init_quotes(&q);
	i = -1;
	while (line[++i])
	{
		quote_enclosure_handle(line[i], &q);
		if (line[i] && line[i] == '*' && !q.dbl && !q.sgl)
		{
			if (i > 0 && line[i - 1] != 92)
				return (i);
			else if (i == 0)
				return (0);
		}
	}
	return (-1);
}

void	init_wildcard_struct(t_wildcard *w)
{
	w->wildcard = NULL;
	w->dirname = NULL;
	w->token = NULL;
	w->s_dir = NULL;
	w->prefix = NULL;
	w->suffix = NULL;
	w->temp = NULL;
	w->file_list = NULL;
	w->current = false;
	w->line_suffix = NULL;
}

/**Go through the command and do all the substitutions
 */
char	*wildcard_handle(t_mini *mini, char *line)
{
	int			i;
	t_wildcard	w;
	
	i = need_wildcard_substitution(line);
	while (i != -1)
	{
		init_wildcard_struct(&w);
		line = substitute_wildcard(mini, line, &w, i);
		i = need_wildcard_substitution(line);
	}
	return (line);
}
