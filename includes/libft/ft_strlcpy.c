/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:11:09 by jrandet           #+#    #+#             */
/*   Updated: 2024/10/18 12:53:56 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*src_start;

	src_start = src;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (--dstsize && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (ft_strlen(src_start));
}
