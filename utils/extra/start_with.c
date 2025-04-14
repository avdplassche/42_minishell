/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_with.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:14 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 15:00:15 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_with(char *string, char *start_string)
{
	int	i;

	i = 0;
	while (string[i] && start_string[i])
	{
		if (!string[i] || string[i] != start_string[i])
			return (0);
		i++;
	}
	return (1);
}
