/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epurstring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:58:39 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:58:40 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_len_dest(char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_space(src[i]))
		i++;
	while (src[i])
	{
		while (!(is_space(src[i])))
		{
			i++;
			j++;
		}
		if (is_space(src[i]))
			j++;
		while (is_space(src[i]))
			i++;
	}
	if (is_space(src[i - 1]))
		j--;
	return (j);
}

/** Epur string by deleting all multiple spaces
 * @return an epured string
*/
char	*epurstring(char *src)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (count_len_dest(src) + 1));
	if (!dest)
		return (NULL);
	while (is_space(src[i]))
		i++;
	while (src[i])
	{
		while (!(is_space(src[i])))
			dest[j++] = src[i++];
		if (is_space(src[i]))
			dest[j++] = ' ';
		while (is_space(src[i]))
			i++;
	}
	if (is_space(src[i - 1]))
		j--;
	dest[j] = '\0';
	return (dest);
}
