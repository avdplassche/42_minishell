
#include "minishell.h"

static void	get_line_into_pipe(t_mini *mini, t_cmd *cmd, int *here_doc_pipe)
{
	char	*line;
	char	*cursor;

	(void)mini;
	DEBUG("DEBUG: heredoc has started, delimiter: %s\n", cmd->redir->pathname);
	while(1)
	{
		line = get_line_from_stdin();
		if (!line)
		{
			break ;
		}
		DEBUG("DEBUG: Read linme is %s\n", line);
		cursor = line;
		while (*cursor && *cursor != '\n')
			cursor++;
		*cursor = '\0';
		DEBUG("after treplacement of \n by 0, %s\n", line);
		if (line[0] != 0 && ft_strcmp(line, cmd->redir->pathname) == 0)
		{
			DEBUG("DEBUG: delimiter found\n");
			free(line);
			break ;
		}
		DEBUG("DEBUG: writing what i read into pipe\n");
		write(here_doc_pipe[1], line, ft_strlen(line));
		write(here_doc_pipe[1], "\n", 1);
		free(line);
	}
	DEBUG("DEBUG: heredoc input collected\n");
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
		DEBUG("handing over the fd to the fd in structure, %d\n", here_doc_pipe[0]);
		cmd->pipe_in_heredoc_read_fd = here_doc_pipe[0];
	}
	return (pid);
}
