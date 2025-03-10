


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


void	print_cmd(t_cmd cmd, char *cmd_line)
{
	int i;
	(void)cmd_line;

	i = 0;
	if (TEST_MODE == 0)
		printf("\n");
	printf(CYAN);
	printf("   Command %d : %s%s¶\n\n", cmd.id, cmd.command, RESET);
	// printf(RESET);
	if (cmd.type == USER)
		printf("	  Type : USER COMMAND\n\n");
	else if (cmd.type == BUILTIN)
		printf("	  Type : BUILTIN\n\n");
	else
		printf("	  Type : INVALID\n\n");
	printf("	  Arg Amount : %d\n\n", cmd.arg_amount);
	if (cmd.args != NULL)
		while (cmd.args[++i])
			printf("	  Arg[%d] %s¶\n", i, cmd.args[i]);
	if (cmd.in_redir_total || cmd.out_redir_total || cmd.in_delimiter_total || cmd.out_appredir_total)
		if (cmd.filename)
			printf("	  Filename : %s¶", cmd.filename);
	printf("\n	  In redir ? : %d\n", cmd.in_redir_total);
	printf("	  Out redir ? : %d\n", cmd.out_redir_total);
	printf("	  In delimiter ? : %d\n", cmd.in_delimiter_total);
	printf("	  Out appredir ? : %d\n", cmd.out_appredir_total);
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
