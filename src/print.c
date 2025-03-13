


#include "../includes/minishell.h"

/** Print a char **, all strings are separated by a new line
 * @param table the char ** to print
 * @param name the name of the char, also to be printed
 *
 */
void	print_char_table(char **table, char *name)
{
	int	i;

	i = -1;
	printf("\nChar ** table :\n\n");
	while (table[++i] != NULL)
		printf("%s [%d] : %s\n", name, i, table[i]);
}

void	print_string(char *string, char *name)
{
	printf("%s : %s\n", name, string);
}

void	print_unexpected_token(char *token)
{
	printf("minishell: error near unexpected token '%s'\n", token);
}

void	print_quote_statement_debug(t_mini *mini, int i, t_quote *q)
{
	printf("line[%d] : %c | sq = %d| dq = %d\n", i, mini->line[i], q->sgl, q->dbl);
}


void	print_cmd(t_cmd cmd, char *cmd_line)
{
	int i;
	(void)cmd_line;

	i = 0;
	if (TEST_MODE == 0)
		printf("\n");
	// printf(CYAN);
	printf("   Command %d : %s¶\n\n", cmd.id, cmd.command);
	printf("   Path : %s¶\n\n", cmd.path);
	// printf(RESET);
	if (cmd.type == USER)
		printf("	  Type : USER COMMAND\n\n");
	else if (cmd.type == BUILTIN)
		printf("	  Type : BUILTIN\n\n");
	else
		printf("	  Type : INVALID\n\n");
	printf("	  Total Args : %d\n\n", cmd.arg_amount);
	if (cmd.args != NULL)
	{
		while (cmd.args[++i])
			printf("	  Arg[%d] : %s¶\n", i, cmd.args[i]);
		printf("\n");
	}
	i = 0;
	printf("	  Total redirections : %d\n\n", cmd.redir_amount);
	if (cmd.redir_amount)
	{
		while (i < cmd.redir_amount)
		{
			printf("	  Redir[%d] : %s ", i, cmd.redir[i].pathname);
			if (cmd.redir[i].type == IN_REDIR)
				printf("(IN REDIR)¶\n");
			else if (cmd.redir[i].type == OUT_REDIR)
				printf("(OUT REDIR)¶\n");
			else if (cmd.redir[i].type == OUT_APPEND)
				printf("(OUT APPEND)¶\n");
			else if (cmd.redir[i].type == HERE_DOC)
				printf("(HERE_DOC)¶\n");
			i++;
		}
		printf("\n");
	}
}

void	debug_parsing_print(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < mini->cmd_amount)
	{
		print_cmd(cmd[i], mini->line);
		printf("\n");
	}
	printf("-----------------------------------------------\n");
}
