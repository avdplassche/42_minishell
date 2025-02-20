/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:37:57 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/20 13:43:34 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i <= len)
	{
		while (haystack[i] == needle[j] && haystack[i] && i < len)
		{
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return (&(*(char *)&haystack[i - j]));
		else
		{
			i = i - j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}
