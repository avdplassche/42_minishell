
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
	while (argc == 1)
	{
		mini.line = readline("Prompt minishell ");
		add_history(mini.line);
		if (!(is_only_spaces(mini.line)) || mini.line[0] != '#')
			parsing(&mini, &cmd);
		//exec(&mini, &cmd);
		free(mini.line);
		mini.line = NULL;
	}

/************************ TEST MODE/ ****************************** */

	if (argc > 1)
	{
		int fd = open(argv[1], O_RDONLY);
		char buffer[10000];
		int i = -1;
		int c = 0;
		int r = read(fd, buffer, 9999);

		buffer[r] = '\0';
		while (buffer[++i])
			if (buffer[i] == '\n')
				c++;
		close(fd);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			perror("error");
		c = 0;
		while (TEST_MODE == 1 && c < ft_atoi(argv[2]))
		{
			mini.line = ft_strtrim(get_next_line(fd), " 	\n");
			printf("\nCOMMAND LINE %d > %s\n\n", c + 1, mini.line);
			if (!(is_only_spaces(mini.line)))
				parsing(&mini, &cmd);
			free(mini.line);
			mini.line = NULL;
			c++;
		}
		close(fd);
	}
/************************ /TEST MODE ***************************** */

	free_mini(&mini);
	return (0);
}
