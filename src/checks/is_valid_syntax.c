/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:41:11 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/22 10:12:30 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_syntax(char *command)
{
	const char	set[8] = "&|><;()";
	int			i;

	i = -1;
	while (command[++i])
		if (!contain_char(set, command[i]))
			return (1);
	DEBUG("%s i = %d\n\n", command, i);
	print_error("minishell: syntax error near unexpected token '%s'\n",
		command, 2);
	return (0);
}
