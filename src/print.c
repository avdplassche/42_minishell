


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
	// int comp;

	// comp = 0;
	i = -1;
	if (TEST_MODE == 0)
		printf("\n");
	// comp = ft_strncmp(get_next_line(fd), cmd.command, ft_strlen(cmd.command));
	// printf("comp : %d\n", comp);
	// if (cmd.id <= 9 && !comp)
	// 	printf(GREEN);
	printf("   Command %d -e : %s$\n\n", cmd.id, cmd.command);
	// printf(RESET);
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
	if (cmd.in_redir_total || cmd.out_redir_total || cmd.in_delimiter_total || cmd.out_appredir_total)
		if (cmd.filename)
			printf("	  Filename : %s\n", cmd.filename);
	printf("	  In redir ? : %d\n", cmd.in_redir_total);
	printf("	  Out redir ? : %d\n", cmd.out_redir_total);
	printf("	  In delimiter ? : %d\n", cmd.in_delimiter_total);
	printf("	  Out appredir ? : %d\n", cmd.out_appredir_total);
}

void	debug_parsing_print(t_mini *mini, t_cmd *cmd)
{
	int	i;
	// int	fd;

	i = -1;
	// printf("\nCommand line : %s\n\n", mini->line);
	// fd = open("test/out_cmd", O_RDONLY);
	// if (fd == -1)
		// perror("fdes");
	while (++i < mini->cmd_amount)
	{
		print_cmd(cmd[i], mini->line);
		printf("\n");
	}
	printf("-----------------------------------------------\n");
	// close(fd);
}
