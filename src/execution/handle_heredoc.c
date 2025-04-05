
#include "minishell.h"
static void	get_line_into_pipe(t_mini *mini, t_cmd *cmd, int *here_doc_pipe)
{
	char	*line;
	char	*cursor;

	(void)mini;
	while(1)
	{
		line = get_line_from_stdin();
		cursor = line;
		while (*cursor && *cursor != '\n')
			cursor++;
		*cursor = '\0';
		if (line[0] != 0 && ft_strcmp(line, cmd->redir->pathname) == 0)
		{
			free(line);
			break ;
		}
		DEBUG("writing into the pipe...\n");
		write(here_doc_pipe[1], line, ft_strlen(line));
		write(here_doc_pipe[1], "\n", 1);
		free(line);
	}
}

int	handle_heredoc(t_mini *mini, t_cmd *cmd)
{
	pid_t 	pid;
	int		here_doc_pipe[2];

	if (pipe(here_doc_pipe) == -1)
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
		close(here_doc_pipe[0]);
		get_line_into_pipe(mini, cmd, here_doc_pipe);
		close(here_doc_pipe[1]);
		exit(EXIT_SUCCESS);
	}
	if (pid != 0)
	{
		close(here_doc_pipe[1]);
		if (cmd->pipe_in_heredoc_read_fd != -1)
			cmd->pipe_in_heredoc_read_fd = -1;
		cmd->pipe_in_heredoc_read_fd = here_doc_pipe[0];
	}
	DEBUG("handle herdoc is returning the pid\n");
	return (pid);
}



// print what is in pipe