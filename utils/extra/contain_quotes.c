/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:58:06 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:58:07 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * To know there is quote in a specific string
 * @param s a string
 * @return - 1 if quote
 * @return - 0 if no quote
*/
bool	contain_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (1);
	}
	return (0);
}
