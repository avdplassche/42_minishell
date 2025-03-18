/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:54:45 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/20 13:46:35 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = -1;
	if (start >= ft_strlen(s))
	{
		dest = ft_strdup("");
		return (dest);
	}
	if (len > ft_strlen(s) - start)
		dest = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (++i < len && start < ft_strlen(s))
	{
		dest[i] = s[start];
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
