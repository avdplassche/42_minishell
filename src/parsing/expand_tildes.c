/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:38:36 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:38:38 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	need_tilde_expand(t_mini *mini)
{
	int		i;
	t_quote	q;

	init_quotes(&q);
	i = -1;
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &q);
		if ((!q.dbl || !q.sgl) && mini->line[i] == '~')
		{
			if (i == 0 && (mini->line[1] == ' ' || !mini->line[i + 1]))
				return (0);
			if (i > 0 && (mini->line[i - 1] == ' '
					&& (!mini->line[i + 1] || mini->line[i + 1])))
				return (i);
		}
	}
	return (-1);
}

char	*get_lonely_tilde(t_mini *mini)
{
	char	*prefix;
	char	*suffix;
	char	*temp;

	prefix = ft_get_env(mini, "HOME");
	str_malloc_check(mini, prefix);
	suffix = ft_substr(mini->line, 1, ft_strlen(mini->line) - 1);
	if (!suffix)
		return (free(prefix), NULL);
	temp = ft_strjoin(prefix, suffix);
	free(suffix);
	free(prefix);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*get_tilde(t_mini *mini, int i)
{
	char	*temp;
	char	*prefix;
	char	*suffix;
	char	*env;

	env = ft_get_env(mini, "HOME");
	str_malloc_check(mini, env);
	prefix = ft_substr(mini->line, 0, i);
	if (!prefix)
		return (free(env), NULL);
	suffix = ft_substr(mini->line, i + 1, ft_strlen(mini->line) - 1 - i);
	if (!suffix)
		return (free(env), free(prefix), NULL);
	temp = join_three_strings(prefix, env, suffix);
	return (free(env), free(prefix), free(suffix), temp);
}

void	sub_tilde(t_mini *mini, int i)
{
	char	*temp;

	if (i == 0)
	{
		temp = get_lonely_tilde(mini);
		str_malloc_check(mini, temp);
	}
	else
	{
		temp = get_tilde(mini, i);
		str_malloc_check(mini, temp);
	}
	mini->line = ft_strdup(temp);
	str_malloc_check(mini, mini->line);
	free(temp);
}

void	expand_tildes(t_mini *mini)
{
	int		i;

	if (!contain_char(mini->line, '~'))
		return ;
	i = need_tilde_expand(mini);
	while (i != -1)
	{
		sub_tilde (mini, i);
		i = need_tilde_expand(mini);
	}
}
