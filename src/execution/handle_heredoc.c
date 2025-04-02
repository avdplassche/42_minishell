
#include "minishell.h"

void	get_line_into_pipe(t_mini *mini, t_cmd *cmd)
{
	char	*line;
	int		i;

	(void)mini;
	while(1)
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
		write(cmd->pipe_in_heredoc->write, line, ft_strlen(line));
		write(cmd->pipe_in_heredoc->write, "\n", ft_strlen(line));
		free(line);
	}
}

void	handle_heredoc(t_mini *mini, t_cmd *cmd)
{
	pid_t pid;

	if (pipe(cmd->pipe_in_heredoc->fildes) == -1)
	{
		mini->last_return = PIPE_ERROR;
		exit_minishell(mini, cmd);
	}
	pid = fork();
	if (pid == -1)
	{
		mini->last_return = FORK_ERROR;
		exit_minishell(mini, cmd);
	}
	if (pid == 0)
	{
		get_line_into_pipe(mini, cmd);
		close(cmd->pipe_in_heredoc->write);

	}


}
