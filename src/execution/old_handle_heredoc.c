
#include "minishell.h"

void	old_get_line_into_pipe(t_mini *mini, t_cmd *cmd)
{
	char	*line;
	int		i;

	while (1)
	{
		line = get_line_from_stdin();
		i = 0;
		while (line[i] && line[i] != '\n')
			i++;
		if (line[0] != 0 && ft_strcmp(line, cmd->redir->pathname) == 0)
		{
			free(line);
			break ;
		}
		write(mini->pipes[0].write, line, ft_strlen(line));
		write(mini->pipes[0].write, "\n", 1);
		free(line);
	}
}

void	old_handle_heredoc(t_mini *mini, t_cmd *cmd)
{
	if (pipe(mini->pipes->fildes) == -1)
	{
		mini->last_return = PIPE_ERROR;
		exit_minishell(mini, cmd);
	}
	get_line_into_pipe(mini, cmd);
	close(mini->pipes->write);
	if (dup2(mini->pipes->read, STDIN_FILENO) == -1)
	{
		mini->last_return = DUP_ERROR;
		exit_minishell(mini, cmd);
	}
	close(mini->pipes[0].read);
}
