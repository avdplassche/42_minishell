/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:19:20 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/25 21:24:44 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	null_terminate_line(char **line)
{
	char	*cursor;

	cursor = *line;
	while (*cursor && *cursor != '\n')
		cursor++;
	*cursor = '\0';
}

static void	get_in_pipe(t_mini *mini, int heredoc_fd, t_redir *redir)
{
	char	*line;
	char	*prompt;
	char	*tmp;

	prompt = string_array_join((char *[]){"Heredoc(", redir->name, ") > ", \
		NULL});
	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
		{
			print_error("minishell: warning: here-document delimited by end-of-file (wanted %s)\n", redir->name, 2);
		}
		null_terminate_line(&line);
		if (line[0] != 0 && ft_strcmp(line, redir->name) == 0)
		{
			free_string_ptr(&line);
			break ;
		}
		tmp = enquote_str(line, 34);
		free(line);
		line = tmp;
		tmp = NULL;
		line = dollar_handle(mini, line);
		tmp = clean_command_quotes(mini, line);
		free(line);
		line = tmp;
		tmp = NULL;
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free_string_ptr(&line);
	}
}

static void	heredoc_child(t_mini *mini, t_pipefd hd_pipe, t_redir *redir)
{
	close(hd_pipe.read);
	hd_pipe.read = -1;
	get_in_pipe(mini, hd_pipe.write, redir);
	close(hd_pipe.write);
	exit_minishell(mini);
}

static void	create_heredoc_process(t_mini *mini, t_redir *redir)
{
	pid_t		pid;
	t_pipefd	hd_pipe;
	int			wstatus;

	(void)wstatus;
	if (pipe(hd_pipe.fildes) == -1)
	{
		perror("ERROR: pipe creation failed:\n");
		mini->last_return = errno;
		exit_minishell(mini);
	}
	pid = fork();
	if (pid == 0)
	{
		signal_child();
		heredoc_child(mini, hd_pipe, redir);
	}
	close(hd_pipe.write);
	redir->heredoc_fd = hd_pipe.read;
	waitpid(pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGINT)
		{
			write(1, "\n", 1);
			mini->last_return = 130;
		}
	}
}

void	handle_heredoc(t_mini *mini, t_cmd *cmd)
{
	int i;
	
	i = 0;
	setup_command_signal(mini);
	while (i < cmd->redir_amount && !mini->last_return)
	{
		if (cmd->redir[i].type == HERE_DOC)
		{
			create_heredoc_process(mini, &cmd->redir[i]);
			if (mini->last_return == 130)
				break ;
		}
		i++;
	}
}
