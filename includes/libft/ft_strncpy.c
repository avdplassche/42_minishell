/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:05:54 by jvoisard          #+#    #+#             */
/*   Updated: 2024/10/15 21:36:27 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strncpy(char *dst, char *src, size_t n)
{
	char	*cursor;

	if (!dst || !src)
		return ;
	cursor = dst;
	while (*src && n--)
		*cursor++ = *src++;
	*cursor = '\0';
}
