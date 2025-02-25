/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:03:42 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/25 00:47:30 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"





/**
 * Counting commands amout, that will be used for pipes.
 * @param line command line
 * @return - number of comands
 * @note prodeed by countint pipe char '|'
 */
int	count_cmd(char *line)
{
	int	i;
	int	count;

	count = 1;
	i = -1;
	while (line[++i])
		if (line[i] == '|')
			count++;
	return (count);
}

t_cmd	*parsing(t_mini *mini)
{
	t_cmd	*cmd_struct;
	int		i;
	int		bin_count;

	i = 0;
	// lister les erreurs de ce genre
	// if (line[i] == '|')
		// error();

	// count number of cmd, malloc(size of (t_cmd) * cmd_amount)

	/*\ order is important /*/

	if (mini->current_line[0] == '$')
	{

	}
	/* case line[0] == '$' */

	if (!(contain_char(mini->current_line, ' ')))
	{

	}
	/* case no spaces */

		// Exemple : ls

		// check if in buildtin
		// check if in bin
		// if yes exec
		// if no : printf()

	bin_count = count_cmd(mini->current_line);
	cmd_struct = (t_cmd *)malloc(sizeof(t_cmd) * bin_count); //can put it in fill_cmd
	fill_cmd_structure(mini, cmd_struct, bin_count);
	printf("\nBin : %s$\n\n", cmd_struct->bin);


	/*second parse*/

		/* case pipe */

			// count pipe amount ?
			// find ' | ', not only '|'


		/* case 1 spaces no pipes no redirection */

			//count number of comands ?



	return (cmd_struct);
}


