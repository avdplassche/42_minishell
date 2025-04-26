/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only_specific_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:59:05 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/26 14:33:26 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_specific_char(char *s, char c)
{
	int	i;

	i = -1;
	if (c && !s[0])
		return (0);
	while (s[++i])
	{
		if (s[i] != c)
			return (0);
	}
	return (1);
}
