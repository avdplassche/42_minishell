/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:08:50 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/25 00:22:51 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * To know id a char is present in a string, should be renamed, isnt it ?
 * @param s a string
 * @param c a char
 * @return - 1 if c is in s
 *
 * @return - 0 if c isn't in s
 * @note can be used to see if a char is in a charset !!!
 */
bool	contain_char(char *s, char c)
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
