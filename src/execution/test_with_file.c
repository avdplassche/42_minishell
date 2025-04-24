
#include "minishell.h"

int	execute_file(t_mini *mini, char *filename)
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
			parsing(mini, cmd);
		free(cmd);
		free(mini->line);
		mini->line = NULL;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return cmd_status;
}
