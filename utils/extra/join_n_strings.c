/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_n_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:59:14 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:59:15 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_n_strings_wildcards(t_mini *mini, t_wildcard *w)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = NULL;
	j = 1;
	if (w->file_amount == 1)
		return (w->file_list[0]);
	str = ft_strjoin(w->file_list[i], w->file_list[j++]);
	str_malloc_wildcard_check(mini, w, str);
	while (j < w->file_amount)
	{
		w->temp = ft_strjoin(str, w->file_list[j]);
		free(str);
		str_malloc_wildcard_check(mini, w, w->temp);
		j++;
		str = ft_strdup(w->temp);
		str_malloc_wildcard_check(mini, w, str);
		free(w->temp);
		w->temp = NULL;
	}
	return (str);
}
