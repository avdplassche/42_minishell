/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:57:58 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:57:59 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * To know if a char is present in a string, should be renamed, isnt it ?
 * @param s a string
 * @param c a char
 * @return - 1 if c is in s
 *
 * @return - 0 if c isn't in s
 * @note can be used to see if a char is in a charset !!!
 */
bool	contain_char(const char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}
