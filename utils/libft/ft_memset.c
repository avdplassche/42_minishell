/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:54:05 by jrandet           #+#    #+#             */
/*   Updated: 2025/03/25 12:52:37 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void	*b, int c, size_t len)
{
	unsigned char	*testpointer;

	testpointer = (unsigned char *)b;
	while (len--)
		*testpointer++ = (unsigned char)c;
	return (b);
}
