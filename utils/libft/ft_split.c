/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:44:25 by alvan-de          #+#    #+#             */
/*   Updated: 2025/03/18 15:48:14 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wordcount(char *s, char c)
{
	int	i;
	int	compt;

	compt = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			compt ++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (compt);
}

static int	ft_wordlen(char *s, char c, int i)
{
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*ft_fill(char *s, char c)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	str = malloc(sizeof(char) * (ft_wordlen(&s[i], c, i) + 1));
	if (!str)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	while (s[i] != c && s[i])
			i++;
	return (str);
}

char	**memory(char **str, int j)
{
	j--;
	while (j >= 0)
		free(str[j--]);
	free(str);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	j = 0;
	i = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			tab[j] = ft_fill(&s[i], c);
			if (!tab[j++])
				return (memory(tab, j));
		}
		while (s[i] != c && s[i])
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
