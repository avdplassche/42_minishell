/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:45:02 by alvan-de          #+#    #+#             */
/*   Updated: 2025/03/18 15:48:14 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		j;
	int		k;
	char	*s2;

	k = 0;
	i = 0;
	j = ft_strlen(s1) - 1;
	if (!s1[i])
	{
		s2 = ft_calloc(1, 1);
		return (s2);
	}
	while (ft_in_set(s1[i], set) == 1)
			i++;
	while (ft_in_set(s1[j], set) == 1 && i < j)
			j--;
	s2 = malloc(sizeof(char) * ((j + 1 - i) + 1));
	if (!s2)
		return (NULL);
	while (j >= i)
		s2[k++] = s1[i++];
	s2[k] = '\0';
	return (s2);
}
