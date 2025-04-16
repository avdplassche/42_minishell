/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_with_identifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:14 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/16 17:41:59 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_with_identifier(char *string, char *identifier)
{
	while (*string && *identifier)
	{
		if (*identifier != *string)
			return (0);
		identifier++;
		string++;
	}
	if (*identifier)
		return (0);
	if (*string == '=' || *string == '\0')
		return (1);
	return (0);
}
