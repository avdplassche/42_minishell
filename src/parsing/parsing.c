/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 02:03:42 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/26 19:49:56 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** Count command amount in command line, that will be used for pipes.
 * @param mini t_mini containing the command line
 * @return number of commands
 * @note proceed by countint pipe char '|'
 */
int	count_cmd(t_mini *mini)
{
	int	i;
	int	count;

	count = 1;
	i = -1;
	while (mini->current_line[++i])
		if (mini->current_line[i] == '|')
			count++;
	return (count);
}

/** Initialize command tokens
 * @param mini t_mini containing the amount of comands in the current line
 * @param cmd command structure
 * @param i index of the cmd structure
 * 
 */
int	init_cmd(t_mini *mini, t_cmd *cmd, int i)
{
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->file_path = NULL;
	cmd->total_cmd = count_cmd(mini);
	cmd->id = i + 1;
	cmd->type = -1;
	cmd->in_redir = 0;
	cmd->out_redir = 0;
	cmd->delimiter = 0;
	cmd->out_appredir = 0;
	cmd->index = 0;
	return (0);
}



/** Count number of quotes in command line
 * @param mini t_mini containing the command line
 * @return number of quotes in command line
 * @note 34 = ' 
 * @note 39 = "
 */
int	quote_amount(t_mini *mini)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (mini->current_line[++i])
		if (mini->current_line[i] == 34 || mini->current_line[i] ==  39)
			count++;
	return (count);
}


int	parsing(t_mini *mini, t_cmd *cmd)
{
	int		cmd_total;
	int		i;

	i = -1;
	if (ft_strncmp("$?", mini->current_line, 2) == 0)
		return (printf("%d: command not found\n", mini->last_return), 0);
	if (quote_amount(mini) % 2 == 1)
		return (printf("quote error\n"), -1); //a revoir


		
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

	cmd_total = count_cmd(mini);
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * cmd_total); //can put it in fill_cmd
	//malloc protection
	while (++i < cmd_total)
	{
		init_cmd(mini, &cmd[i], i);
		fill_cmd_structure(mini, cmd);
	}
	if (DEBUGG_PARSING == 1)
		debug_parsing(mini, cmd);


	/*second parse*/

		/* case pipe */

			// count pipe amount ?
			// find ' | ', not only '|'


		/* case 1 spaces no pipes no redirection */

			//count number of comands ?



	return (0);
}


