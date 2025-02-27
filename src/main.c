
#include "../includes/minishell.h"


/** Frees char ** variables
 */
void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

/** Frees t_mini mini, used when leaving minishell
 *maybe when signals exit the program
 */
void	free_mini(t_mini *mini)
{
	free_double_pointer(mini->envp);
	free_double_pointer(mini->builtins);
	free_double_pointer(mini->paths);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	t_cmd	cmd;

	init_mini(&mini, envp);
	//malloc protection
	printf("\n");
	while (TEST_MODE == 0)
	{
		mini.current_line = readline("Prompt minishell ");
		add_history(mini.current_line);
		if (!(is_spaces_only(mini.current_line)))
			parsing(&mini, &cmd);
		free(mini.current_line);
		mini.current_line = NULL;
	}

/********************** TEST MODE ****************************** */

	int fd = open("TESTMODE", O_RDONLY);
	char buffer[10000];
	int i = -1;
	int c = 0;
	int r = read(fd, buffer, 9999);

	buffer[r] = '\0';
	while (buffer[++i])
		if (buffer[i] == '\n')
			c++;
	close(fd);
	fd = open("TESTMODE", O_RDONLY);
	if (fd == -1)
		perror("error");
	while (TEST_MODE == 1 && c >= 0)
	{
		mini.current_line = get_next_line(fd);
		if (!(is_spaces_only(mini.current_line)))
			parsing(&mini, &cmd);
		free(mini.current_line);
		mini.current_line = NULL;
		c--;
	}
	close(fd);
	free_mini(&mini);
	return (0);
}
