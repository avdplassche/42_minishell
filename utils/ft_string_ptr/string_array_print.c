/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:04:23 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 17:05:03 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	contains_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/**
 * get the length of an array of pointers
 * @param str is the array of pointers you want to print to the standard out
 * @return - void, prints in terminal
 */
void	string_array_print(t_cmd *cmd, char **string_array)
{
	int		i;
	char	*equal_pos;

	i = 0;
	while (string_array[i])
	{
		if (cmd->is_export)
		{
			equal_pos = ft_strchr(string_array[i], '=');
			if (equal_pos)
				printf("declare -x %.*s=\"%s\"\n", \
					(int)(equal_pos - string_array[i]), string_array[i], \
					(equal_pos + 1));
			else
				printf("declare -x %s\n", string_array[i]);
		}
		else if (contains_equal(string_array[i]) && !cmd->is_export)
		{
			printf("%s\n", string_array[i]);
		}
		i++;
	}
}
