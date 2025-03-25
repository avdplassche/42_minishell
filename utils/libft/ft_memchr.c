/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:08:45 by jrandet           #+#    #+#             */
/*   Updated: 2025/03/25 13:54:59 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*testpointer;
	unsigned char	chr;

	testpointer = (unsigned char *)s;
	chr = (char)c;
	while (n--)
	{
		if (*testpointer == chr)
			return (testpointer);
		testpointer++;
	}
	return (NULL);
}
