


#include "minishell.h"


static int	execute_file(t_mini *mini, char *filename)
{
	t_cmd 	*cmd;
	int		fd;
	char	*line;
	int		cmd_status = 0;

	cmd = NULL;
	fd = open(filename, O_RDONLY, 0666);
	if (fd == -1)
		return(-1);
	line= get_next_line(fd);
	while (line)
	{
		if (!*line || *line == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		mini->line = ft_strtrim(line, SPACES);
		free(line);
		line = NULL;
		mini->cmd_count = count_cmd(mini);
		mini->cursor = 0;
		if (!(is_only_spaces(mini->line)) && mini->line[0] != '#')
			cmd_status = parsing(mini, cmd);
		free(cmd);
		free(mini->line);
		mini->line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	return cmd_status;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	t_cmd	*cmd;
	char	*input;

	if (init_mini(&mini, envp) == -1)
		return (EXIT_FAILURE);
	while (argc == 1)
	{
		cmd = NULL;
		mini.cursor = 0;
		signal_list();
		input = readline("Prompt minishell ➤ ");
		if (input == NULL)
		{
			mini.should_exit = true;
			break;
		}
		mini.line = ft_strtrim(input, SPACES);
		free(input);
		mini.cmd_count = count_cmd(&mini);
		add_history(mini.line);
		if ((!(is_only_spaces(mini.line)) || mini.line[0] != '#') && mini.line[0])
			parsing(&mini, cmd);
		if (mini.should_exit)
			break;
		if (mini.line)
			free(mini.line);
		mini.line = NULL;
	}

/************************ TEST MODE/ ****************************** */
	if (argc == 2)
	{
		int script_status = execute_file(&mini, argv[1]);
		mini.last_return = script_status;
	}
	if (argc == 3)
	{
		int fd = open(argv[1], O_RDONLY);
		char buffer[10000];
		int c = 0;
		int r = read(fd, buffer, 9999);
		char	*next_line = NULL;

		cmd = NULL;
		buffer[r] = '\0';
		close(fd);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			perror("error");
		while (TEST_MODE == 1 && c < ft_atoi(argv[2]))
		{
			next_line = get_next_line(fd);
			mini.line = ft_strtrim(next_line, SPACES);
			free(next_line);
			mini.cmd_count = count_cmd(&mini);
			mini.cursor = 0;
			DEBUG("\nCOMMAND LINE %d ➤ %s¶\n\n", c + 1, mini.line);
			if (!(is_only_spaces(mini.line)) || mini.line[0] != '#')
				parsing(&mini, cmd);
			free(cmd);
			free(mini.line);
			mini.line = NULL;
			c++;
		}
		close(fd);
	}

/************************ /TEST MODE ***************************** */

	free_mini(&mini);
	//printf("mini %d\n", mini.last_return);
	DEBUG_CLOSE;
	return (mini.last_return);
}
