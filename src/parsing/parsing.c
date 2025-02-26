/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:03:42 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/26 02:47:43 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** Initialize command tokens
 * @param cmd command structure
 * @param i index of the cmd structure
 * @param bin_amount total number of commands
 */
t_cmd	init_cmd(t_cmd cmd, int i, int bin_amount)
{
	cmd.bin = NULL;
	cmd.args = NULL;
	cmd.fd_path = NULL;
	cmd.pipe_amount = bin_amount;
	cmd.id = i + 1;
	cmd.builtin = 0;
	cmd.in_redir = 0;
	cmd.out_redir = 0;
	cmd.delimiter = 0;
	cmd.out_appredir = 0;
	cmd.index = 0;
	return (cmd);
}


/** Counting commands amount, that will be used for pipes.
 * @param line command line
 * @return number of comands
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
	t_cmd	*cmd;
	int		i;
	int		bin_count;

	i = -1;
	if (ft_strncmp("$?", mini->current_line, 2) == 0)
		return (printf("%d: command not found\n", mini->last_return), NULL);
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
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * bin_count); //can put it in fill_cmd
	while (++i < bin_count)
	{
		cmd[i] = init_cmd(cmd[i], i, bin_count);
		fill_cmd_structure(mini, cmd, bin_count);
	}
	if (DEBUGG_PARSING == 1)
	{
		i = -1;
		printf("\nTotal commands : %d\n", bin_count);
		while (++i < bin_count)
			print_cmd(cmd[i], mini->current_line);
	}

	/*second parse*/

		/* case pipe */

			// count pipe amount ?
			// find ' | ', not only '|'


		/* case 1 spaces no pipes no redirection */

			//count number of comands ?



	return (cmd);
}


