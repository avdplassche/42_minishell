/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:37:51 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/20 13:04:29 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
