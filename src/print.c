


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

	i = -1;
	if (TEST_MODE == 0)
		printf("\n");
	printf("   Command %d\n\n", cmd.id);
	printf("	  Bin : %s\n", cmd.command);
	printf("	  Args  : ");
	if (cmd.args != NULL)
	{
		while (cmd.args[++i])
			printf("%s ", cmd.args[i]);
	}
	else
		printf("(null)\n");
	printf("	  Filename : %s ", cmd.filename);
	if (cmd.is_path == true)
		printf("(path)\n");
	else
		printf("(filename)\n");
	if (cmd.type == BIN)
		printf("	  Type : binary\n");
	else if (cmd.type == BUILTIN)
		printf("	  Type : builtin\n");
	else
		printf("	  Type : invalid command\n");
}

void	debug_parsing(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = -1;
	// printf("\nCommand line : %s\n\n", mini->line);
	while (++i < cmd->total_cmd)
	{
		print_cmd(cmd[i], mini->line);
		printf("\n");
	}
	printf("-----------------------------------------------\n");
}
