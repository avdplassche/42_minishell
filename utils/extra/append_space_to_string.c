/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_space_to_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:57:51 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:57:52 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_space_to_string(t_mini *mini, t_wildcard *w, char **str)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(*str);
	str_malloc_wildcard_check(mini, w, temp);
	free(*str);
	*str = NULL;
	*str = ft_strjoin(temp, " ");
	str_malloc_wildcard_check(mini, w, *str);
	free(temp);
	temp = NULL;
}
