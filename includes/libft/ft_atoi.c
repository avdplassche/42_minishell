/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:34:56 by jrandet           #+#    #+#             */
/*   Updated: 2024/10/12 11:20:30 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	countsign;

	countsign = 1;
	result = 0;
	while (*str && ((9 <= *str && *str <= 13) || *str == ' '))
		str++;
	if (*str == '-')
		countsign = -countsign;
	if (*str == '-' || *str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	if (countsign == -1)
		return (countsign * result);
	return (result);
}
