
#include "minishell.h"

static void	get_line_into_pipe(t_mini *mini, t_cmd *cmd, int *here_doc_pipe, t_redir *redir)
{
	char	*line;
	//char	*expanded_line;
	char	*cursor;
	char	*prompt;

	prompt = string_array_join((char *[]){"Heredoc(", cmd->redir->name, ") > ", NULL});
	while(1)
	{
		line = readline(prompt);
		cursor = line;
		while (*cursor && *cursor != '\n')
			cursor++;
		*cursor = '\0';
		if (line[0] != 0 && ft_strcmp(line, redir->name) == 0)
		{
			DEBUG("delimiter matched\n");
			free(line);
			break ;
		}
		//line = enquote_str(line, 34);
		line = dollar_handle(mini, line);
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
	get_line_into_pipe(mini, cmd, here_doc_pipe, redir);
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
