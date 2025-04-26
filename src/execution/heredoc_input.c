/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 00:28:44 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 13:00:45 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	treat_heredoc_line_expanssion(t_mini *mini, char **line)
{
	char	*tmp;

	tmp = enquote_str(*line, 34);
	free(*line);
	*line = tmp;
	tmp = NULL;
	*line = dollar_handle(mini, *line);
	tmp = clean_command_quotes(mini, *line);
	free(*line);
	*line = tmp;
	tmp = NULL;
}

void	null_terminate_heredoc_line(char **line)
{
	char	*cursor;

	cursor = *line;
	while (*cursor && *cursor != '\n')
		cursor++;
	*cursor = '\0';
}

void	get_heredoc_imput_in_pipe(t_mini *mini, int heredoc_fd, t_redir *redir)
{
	char	*line;
	char	*prompt;

	prompt = "> ";
	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
		{
			print_error("here-doc delimited by end-of-file (wanted %s)\n", \
				redir->name, 2);
		}
		null_terminate_heredoc_line(&line);
		if (line[0] != 0 && ft_strcmp(line, redir->name) == 0)
		{
			free_string_ptr(&line);
			break ;
		}
		treat_heredoc_line_expanssion(mini, &line);
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free_string_ptr(&line);
	}
}
