/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:37:51 by alvan-de          #+#    #+#             */
/*   Updated: 2025/03/18 15:48:14 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	ch;

	ch = (unsigned char)c;
	i = 0;
	if (ch == 0)
	{
		while (s[i])
			i++;
		return (&(*(char *)&s[i]));
	}
	else
	{
		while (s[i])
		{
			if (s[i] == ch)
				return (&(*(char *)&s[i]));
			i++;
		}
	}
	return (NULL);
}
