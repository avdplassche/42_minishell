


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


	i = -1;
	if (TEST_MODE == 0)
		printf("\n");
	printf("   Command %d -e : %s$\n\n", cmd.id, cmd.command);
	if (cmd.type == N_BUILTIN)
		printf("	  Type : binary or invalid\n");
	else if (cmd.type == BUILTIN)
		printf("	  Type : builtin\n");
	else
		printf("	  Type : binary or invalid\n");
	printf("	  Args  : ");
	if (cmd.args != NULL)
		while (cmd.args[++i])
			printf("%s ", cmd.args[i]);
	else
		printf("(null)\n");
	printf("	  Filename : %s ", cmd.filename);
	if (cmd.is_path == true)
		printf("(path)\n");
	else
		printf("(filename)\n");
}

void	debug_parsing(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = -1;
	// printf("\nCommand line : %s\n\n", mini->line);
	while (++i < mini->cmd_amount)
	{
		print_cmd(cmd[i], mini->line);
		printf("\n");
	}
	printf("-----------------------------------------------\n");
}
