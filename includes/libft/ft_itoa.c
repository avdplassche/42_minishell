/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:54:23 by jrandet           #+#    #+#             */
/*   Updated: 2024/10/16 13:22:24 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	count_div;

	count_div = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count_div++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		count_div++;
	}
	return (count_div);
}

static char	*fill_string(char *str, int n)
{
	if (n == 0)
	{
		*str = '0';
		return (str);
	}
	while (n != 0)
	{
		*str-- = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		int_size;
	char	*int_string;
	char	*end;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	int_size = get_size(n);
	if (int_size == 0)
		return (NULL);
	int_string = (char *)malloc(sizeof(char) * (int_size + 1));
	if (!int_string)
		return (NULL);
	int_string[int_size] = '\0';
	if (n < 0)
	{
		*int_string = '-';
		n = -n;
	}
	end = int_string + int_size - 1;
	fill_string(end, n);
	return (int_string);
}
