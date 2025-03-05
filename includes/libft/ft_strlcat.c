/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:56:02 by jrandet           #+#    #+#             */
/*   Updated: 2024/10/18 14:02:51 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*d;
	char	*s;
	size_t	len_dst;
	size_t	remaining_buffer;

	len_dst = ft_strlen(dst);
	s = (char *)src;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize <= len_dst)
		return (dstsize + ft_strlen(src));
	d = dst + len_dst;
	remaining_buffer = dstsize - len_dst - 1;
	while (*s && remaining_buffer--)
		*d++ = *s++;
	*d = '\0';
	return (len_dst + ft_strlen(src));
}
