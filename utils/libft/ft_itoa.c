/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:07:49 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/08 12:24:07 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*number;
	long	num;

	num = n;
	i = ft_intlen(num);
	number = malloc(sizeof(char) * (ft_intlen(num) + 1));
	if (!number)
		return (NULL);
	if (num < 0)
		num = -num;
	while (i > 0)
	{
		number[--i] = num % 10 + 48;
		num = num / 10;
	}
	if (n < 0)
		number[0] = '-';
	number[ft_intlen(n)] = '\0';
	return (number);
}

