/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:02:48 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 17:02:51 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * get the length of an array of pointers
 * @param str is the array of pointers you want the size of
 * @param variablelen is the length (int) of the variable
 * @return - size (type size_t) of the array of pointers
 */
size_t	string_array_len(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
