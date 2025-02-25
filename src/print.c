


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

void	print_cmd(t_cmd cmd)
{
	int i;

	i = -1;
	printf("\n\n");
	
	printf("   Command %d\n\n", cmd.id);
	printf("	  Bin : '%s'\n", cmd.bin);
	printf("	  Args  : ");
	if (cmd.args != NULL)
	{ 
		while (cmd.args[++i])
			printf("%s ", cmd.args[i]);
	}
	else
		printf("(null)\n");
	printf("	  Pathname : %s\n", cmd.fd_path);
	if (cmd.builtin == 1)
		printf("	  Builtin : YES\n");
	else
		printf("	  Builtin : NO\n");
	printf("\n");
}
