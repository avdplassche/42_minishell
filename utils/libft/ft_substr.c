/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:54:45 by alvan-de          #+#    #+#             */
/*   Updated: 2025/03/18 15:48:14 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
