/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:58:59 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:59:00 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** Check if string is composed of spaces only
 * @return - 1 if only space
 * @return - 0 if there is other characters
 */
int	is_only_spaces(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!(is_space(s[i])))
			return (0);
	}
	return (1);
}
