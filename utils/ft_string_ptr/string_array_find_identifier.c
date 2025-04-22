/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_find_identifier.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:24:54 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 17:42:02 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*string_array_find_identifier(char	**string_array, char *identifier)
{
	while (*string_array)
	{
		if (start_with_identifier(*string_array, identifier))
			return (*string_array);
		string_array++;
	}
	return (NULL);
}
