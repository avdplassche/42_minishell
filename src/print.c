/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:49 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 14:18:37 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** Print a char **, all strings are separated by a new line
 * @param table the char ** to print
 * @param name the name of the char, also to be printed
 *
 */
void	print_char_table(char **table, char *name)
{
	int	i;

	i = -1;
	DEBUG("\nchar **%s :\n\n", name);
	while (table[++i] != NULL)
		DEBUG("%s [%d] : %s\n", name, i, table[i]);
}

void	print_string(char *string, char *name)
{
	DEBUG("%s : %s\n", name, string);
}

void	print_quote_statement_debug(t_mini *mini, int i, t_quote *q)
{
	DEBUG("line[%d] : %c | sq = %d| dq = %d\n", i, mini->line[i], q->sgl, q->dbl);
}


void	print_cmd(t_cmd cmd, char *cmd_line)
{
	int i;
	(void)cmd_line;

	i = -1;
	if (TEST_MODE == 0)
		DEBUG("\n");
	// DEBUG(CYAN);
	DEBUG("   Command %d : %s¶\n\n", cmd.id, cmd.command);
	DEBUG("   Path : %s¶\n\n", cmd.path);
	// DEBUG(RESET);
	if (cmd.type == USER)
		DEBUG("	  Type : USER COMMAND\n\n");
	else if (cmd.type == BUILTIN)
		DEBUG("	  Type : BUILTIN\n\n");
	else
		DEBUG("	  Type : INVALID\n\n");
	DEBUG("	  Total Args : %d\n\n", cmd.arg_amount);
	if (cmd.args != NULL)
	{
		while (cmd.args[++i])
			DEBUG("	  Arg[%d] : %s¶\n", i, cmd.args[i]);
		DEBUG("	  Arg[%d] : %s¶\n", i, cmd.args[i]);
		DEBUG("\n");
	}
	i = 0;
	DEBUG("	  Total redirections : %d\n\n", cmd.redir_amount);
	if (cmd.redir_amount)
	{
		while (i < cmd.redir_amount)
		{
			DEBUG("	  Redir[%d] : %s ", i, cmd.redir[i].name);
			if (cmd.redir[i].type == IN_REDIR)
				DEBUG("(IN REDIR)¶\n");
			else if (cmd.redir[i].type == OUT_REDIR)
				DEBUG("(OUT REDIR)¶\n");
			else if (cmd.redir[i].type == OUT_APPEND)
				DEBUG("(OUT APPEND)¶\n");
			else if (cmd.redir[i].type == HERE_DOC)
				DEBUG("(HERE_DOC)¶\n");
			i++;
		}
		DEBUG("\n");
		DEBUG("	  HEREDOC Amount : %d\n\n", cmd.heredoc_amount);
	}
	//DEBUG("	  command amount : %d\n\n", cmd.redir_amount")
}

