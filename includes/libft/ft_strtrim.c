/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:34:02 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/18 14:30:46 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	int		len;

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
	len = s1 - start + 1;
	if (len <= 0)
		return (ft_calloc(1, 1));
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, start, len + 1);
	trimmed[len] = '\0';
	return (trimmed);
}
