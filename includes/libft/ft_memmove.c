/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 19:40:54 by jrandet           #+#    #+#             */
/*   Updated: 2024/10/14 15:07:20 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*_dst;
	char	*_src;

	if (!dst && !src)
		return (0);
	_src = (char *)src;
	_dst = (char *)dst;
	if (_dst < _src)
	{
		while (n--)
			*(_dst++) = *(_src++);
	}
	else if (_dst > _src)
	{
		_src += n;
		_dst += n;
		while (n--)
			*(--_dst) = *(--_src);
	}
	return (dst);
}
