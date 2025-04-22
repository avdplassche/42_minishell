/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:06:53 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/22 18:56:48 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_in_pipe(t_mini *mini, int *hd_pipe, t_redir *redir)
{
	char	*line;
	char	*cursor;
	char	*prompt;
	char	*tmp;

	prompt = "> ";
	while (1)
	{
		line = readline(prompt);
		cursor = line;
		while (*cursor && *cursor != '\n')
			cursor++;
		*cursor = '\0';
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
		line = clean_command_quotes(mini, line);
		write(hd_pipe[1], line, ft_strlen(line));
		write(hd_pipe[1], "\n", 1);
		free_string_ptr(&line);
	}
}

static void	setup_heredoc_input(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	int		hd_pipe[2];

	if (pipe(hd_pipe) == -1)
	{
		mini->last_return = PIPE_ERROR;
		exit_minishell(mini, cmd);
	}
	get_in_pipe(mini, hd_pipe, redir);
	close(hd_pipe[1]);
	redir->heredoc_fd = hd_pipe[0];
}

void	process_all_heredocs(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redir_amount)
	{
		if (cmd->redir[i].type == HERE_DOC)
		{
			setup_heredoc_input(mini, cmd, &cmd->redir[i]);
		}
		i++;
	}
}
