
#include "minishell.h"



void	handle_signal(void)
{


}

// void	loading()
// {
// 	int i;

// 	i = -1;
// 	while (++i < 20)
// 	{
// 		printf("■");
// 		usleep(30 * 1000);
// 	}
// 	printf("\n");
// }

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	t_cmd	*cmd;

	// loading();
	if (init_mini(&mini, envp) == -1)
		return (EXIT_FAILURE);
	printf("\n");
	while (argc == 1)
	{

		cmd = NULL;
		mini.cursor = 0;
		mini.line = ft_strtrim(readline("Prompt minishell "), SPACES);
		// if (!(ft_strncmp(mini.line, "exit", 4)))
		mini.cmd_amount = count_cmd(&mini);
		// 	return (free (mini.line), free_mini(&mini), EXIT_SUCCESS);
		add_history(mini.line);
		if (!(is_only_spaces(mini.line)) || mini.line[0] != '#')
			parsing(&mini, cmd);
		// signal(g_sig, handle_signal);
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

		cmd = NULL;
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
			mini.line = ft_strtrim(get_next_line(fd), SPACES);
			mini.cmd_amount = count_cmd(&mini);
			mini.cursor = 0;
			DEBUG("\nCOMMAND LINE %d ➤ %s¶\n\n", c + 1, mini.line);
			if (!(is_only_spaces(mini.line)) || mini.line[0] != '#')
			{
				parsing(&mini, cmd);
				//exec_mini(&mini, cmd);
			}
			free(cmd);
			free(mini.line);
			mini.line = NULL;
			c++;
		}
		close(fd);
	}

/************************ /TEST MODE ***************************** */

	free_mini(&mini);
	DEBUG_CLOSE;
	return (0);
}

