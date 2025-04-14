/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:58:45 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:58:46 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_alpha(char *s1, char *s2)
{
	size_t	i;
	char	c1;
	char	c2;

	i = 0;
	while (s1[i] && s2[i])
	{
		c1 = ft_toupper(s1[i]);
		c2 = ft_toupper(s2[i]);
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (ft_toupper(s1[i]) - ft_toupper(s2[i]));
}
