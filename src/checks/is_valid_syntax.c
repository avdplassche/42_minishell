/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:41:11 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:41:39 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_syntax(char *command)
{
	const char	set[7] = "&|><;()";
	int			i;

	i = -1;
	while (command[++i])
		if (!contain_char(set, command[i]))
			return (1);
	print_error("minishell: syntax error near unexpected token '%s'\n",
		command, 2);
	return (0);
}
