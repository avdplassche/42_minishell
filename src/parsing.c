/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:03:42 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/21 17:08:09 by alvan-de         ###   ########.fr       */
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


/**
 * Function testing if the first char of the line is part of the command.
 * @param c char to check
 * @return 1 if its part of the command
 * @return 0 if it's another character
 */
int	check_line_first_char(char c)
{
	char	*set;
	int		i;

	i = -1;
	set = "|<>?$#%";
	while (set[++i])
		if (c == set[i])
			return (0);
	return (1);
}
/**
 * Counting commands amout, that will be used for pipes
 * @param c char to check
 * @return 1 if its part of the command
 * @return 0 if it's another character
 */
int	count_cmd(char *line)
{
	int	i;

	i = 0;
	// while (check_line_first_char(line[i]) == 1)


}

int	parsing(char *line)
{
	int	cmd_amount;
	int	i;
	char *cmd;

	cmd_amount = count_cmd(line);
	i = 0;

	// chek if all comands exists

	while (i < cmd_amount)
	{
		cmd = get_next_cmd_index(*line);  //strdup ?
		if (cmd_exists(cmd))
			i++;
		else
			return (-1)
	}

	// count number of cmd, malloc(size of (t_cmd) * cmd_amount)

	/*\ order is important /*/

	/* case line[0] == '$' */

	if (line[0] == '$')

	/* case line[0] == '<' */

	if (line[0] == '$')

	/* case line[0] == '>' */

		// a bit weird, just create an empty file, handle with creat or cat ?

	/* case no spaces */

		// Exemple : ls

		// check if in buildtin
		// check if in bin
		// if yes exec
		// if no : printf()

	if (!(contain_char(line, ' ')))

	/* case pipe */

		// count pipe amount ?
		// find ' | ', not only '|'


	/* case 1 spaces no pipes no redirection */

		//count number of comands ?












}


