/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:58:10 by jrandet           #+#    #+#             */
/*   Updated: 2024/10/11 10:31:23 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*iterator;

	iterator = (char *)s;
	while (*iterator)
		iterator++;
	while (iterator >= s)
	{
		if (*iterator == (char)c)
			return ((char *)iterator);
		iterator--;
	}
	return (NULL);
}
