
#include "minishell.h"

static void	get_line_into_pipe(t_mini *mini, t_cmd *cmd, int *here_doc_pipe)
{
	char	*line;
	char	*cursor;
	//char	*prompt;
	//char	**array_of_strings;
	//char	*expanded_line;

	(void)mini;
	//array_of_strings = (char *[3]){"heredoc delimiter: ", cmd->redir->name, "> "};
	//prompt = string_array_join(array_of_strings);
	while(1)
	{
		//line = readline(prompt)
		line = get_line_from_stdin();
		cursor = line;
		DEBUG("pathname is worth: %s\n", cmd->redir->name);
		while (*cursor && *cursor != '\n')
			cursor++;
		*cursor = '\0';
		if (line[0] != 0 && ft_strcmp(line, cmd->redir->name) == 0)
		{
			DEBUG("delimiter matched\n");
			free(line);
			break ;
		}
		DEBUG("writing %s into the pipe...\n", line);
		write(here_doc_pipe[1], line, ft_strlen(line));
		write(here_doc_pipe[1], "\n", 1);
		free(line);
		line = NULL;
	}
}

static void	setup_heredoc_input(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	int		here_doc_pipe[2];

	if (pipe(here_doc_pipe) == -1)
	{
		mini->last_return = PIPE_ERROR;
		exit_minishell(mini, cmd);
	}
	get_line_into_pipe(mini, cmd, here_doc_pipe);
	close(here_doc_pipe[1]);
	redir->heredoc_fd = here_doc_pipe[0];
}

void	process_all_heredocs(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	DEBUG("cmd->heredocamount is worth %d\n",  cmd->heredoc_amount);
	while (i < cmd->redir_amount)
	{
		if (cmd->redir[i].type == HERE_DOC)
		{
			setup_heredoc_input(mini, cmd, &cmd->redir[i]);
		}
		i++;
	}
}
