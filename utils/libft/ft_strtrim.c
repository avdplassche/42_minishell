/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:01:25 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/26 13:06:48 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_charset(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	char	*start;

	if (!s1)
		return (ft_calloc(1, 1));
	if (s1[0] == '\0')
		return (ft_calloc(1, 1));
	while (*s1 && (is_in_charset(*s1, set)))
		s1++;
	start = (char *)s1;
	if (*s1 != '\0')
	{
		s1 += ft_strlen(s1) - 1;
		while (s1 > start && is_in_charset(*s1, set))
			s1--;
	}
	if (s1 - start + 1 <= 0)
		return (ft_calloc(1, 1));
	trimmed = malloc(s1 - start + 1 + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, start, s1 - start + 1 + 1);
	trimmed[s1 - start + 1] = '\0';
	return (trimmed);
}
