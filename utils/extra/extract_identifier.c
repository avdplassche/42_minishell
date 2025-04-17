/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_identifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:06:31 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/17 12:53:22 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_identifier(t_mini *mini, char *src)
{
	int		char_index;
	char	*identifier;

	char_index = 0;
	while (src[char_index] && src[char_index] != '=')
		char_index++;
	identifier = ft_calloc((char_index + 1), sizeof(char));
	if (!identifier)
		mini->last_return = MALLOC_ERROR;
	ft_strlcpy(identifier, src, char_index + 1);
	return (identifier);
}
