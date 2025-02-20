/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:32:09 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/20 13:44:21 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*tab;

	i = -1;
	tab = malloc(size * count);
	if (!tab)
		return (NULL);
	while (++i < count * size)
		*(unsigned char *)(tab + i) = 0;
	return (tab);
}
