/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:05:12 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 17:15:02 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_big_array(char **original_arr, char **big_arr, char *new_ptr)
{
	int	i;

	i = -1;
	while (original_arr[++i])
	{
		big_arr[i] = ft_strdup(original_arr[i]);
		free_string_ptr(&original_arr[i]);
		if (!big_arr[i])
		{
			while (--i >= 0)
				free(big_arr[i]);
			free(*big_arr);
			return (NULL);
		}
	}
	big_arr[i] = ft_strdup(new_ptr);
	if (!big_arr[i])
	{
		while (--i >= 0)
			free(big_arr[i]);
		free(big_arr);
		return (NULL);
	}
	free_string_ptr(&new_ptr);
	return (big_arr);
}

char	**string_array_push(char **original_arr, char *new_ptr)
{
	char	**big_array;
	char	**current;
	int		original_len;

	if (!*original_arr)
	{
		big_array = ft_calloc(2, sizeof(char *));
		if (!big_array)
			return (NULL);
		current = big_array;
		*current = ft_strdup(new_ptr);
		*(current + 1) = NULL;
		return (big_array);
	}
	else
	{
		original_len = string_array_len(original_arr);
		big_array = ft_calloc(original_len + 2, sizeof(char *));
		if (!big_array)
		{
			return (NULL);
		}
	}
	return (fill_big_array(original_arr, big_array, new_ptr));
}
