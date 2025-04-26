/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:02:59 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 17:03:28 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * To create the key format of the variable in the env array
 * @param dest_ptr is an array where the two pointers will be concatenated. 
 * 
 * @param prefix is the first pointer (in these cases "PATH=")
 * @param suffix is the second pointer (in these cases the 
 * @return is void because i edit the pointer directly
 *
 * @return none, void
 * @note does not free anything
 * @note mainly used in execution 
 */
void	string_build(char **dest_ptr, char *prefix, char *suffix)
{
	int	i;
	int	j;

	i = 0;
	while (prefix[i])
	{
		(*dest_ptr)[i] = prefix[i];
		i++;
	}
	j = 0;
	while (suffix[j])
	{
		(*dest_ptr)[i] = suffix[j];
		i++;
		j++;
	}
	(*dest_ptr)[i] = '\0';
}
