/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:03:42 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/20 17:42:08 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//make a structure ?
/*
typedef struct t_cmd
{
	char		*bin;
	char		*arg;
	bool		builtins;
	char		**path; ??
}				s_cmd;
*/

void	parsing(char *line)
{
	/*\ order is important /*/

	/* case line[0] == '$'  */

	/* case line[0] == '<'  */

	/* case line[0] == '>'  */

	// a bit weird, just create an empty file, handle with creat or cat ?

	/* case no spaces  */

	// Exemple : ls

	// check if in buildtin
	// check if in bin
	// if yes exec
	// if no : printf()

	/* case pipe  */




	/* case 1 spaces  */


	if (line[0] == '$')

	if (!(contain_char(line, ' ')))







}


