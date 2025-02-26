/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:03:42 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/26 18:09:32 by alvan-de         ###   ########.fr       */
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
	cmd.command = NULL;
	cmd.args = NULL;
	cmd.file_path = NULL;
	cmd.total_cmd = bin_amount;
	cmd.id = i + 1;
	cmd.type = -1;
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
 * @note proceed by countint pipe char '|'
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
	int		cmd_amount;
	int		i;

	i = -1;
	if (ft_strncmp("$?", mini->current_line, 2) == 0)
		return (printf("%d: command not found\n", mini->last_return), NULL);
		
	// lister les erreurs de ce genre
	// if (line[0] == '|')
	// if (nb of '' or "" % 2 != 0)

		// error();

	if (mini->current_line[0] == '$')
	{
		
	}
	
	/* case line[0] == '$' */

	if (!(contain_char(mini->current_line, ' ')))
	{
		//if (cmd_exists cmd->bin
		//
	}
	/* case no spaces */

		// Exemple : ls

		// check if in buildtin
		// check if in bin
		// if yes exec
		// if no : printf()

	cmd_amount = count_cmd(mini->current_line);
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * cmd_amount); //can put it in fill_cmd
	//malloc protection
	while (++i < cmd_amount)
	{
		cmd[i] = init_cmd(cmd[i], i, cmd_amount);
		fill_cmd_structure(mini, cmd, cmd_amount);
	}
	if (DEBUGG_PARSING == 1)
		debug_parsing(mini, cmd, cmd_amount);

	/*second parse*/

		/* case pipe */

			// count pipe amount ?
			// find ' | ', not only '|'


		/* case 1 spaces no pipes no redirection */

			//count number of comands ?



	return (cmd);
}


