/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:57:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/20 15:16:08 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_redir(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	if (redir->heredoc_fd != -1)
	{
		dup2_fd(mini, cmd, redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
	}
}

static void	handle_out_append(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	int	fd;

	fd = open(redir->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->name);
		free_cmd(mini, cmd);
		free_mini(mini);
		exit(EXIT_FAILURE);
	}
	dup2_fd(mini, cmd, fd, STDOUT_FILENO);
	close(fd);
}

static void	print_and_set_error(t_mini *mini, t_redir *redir, char *s,  int error_number)
{
	print_error(s, redir->name, 2);
	mini->last_return = error_number;
}

static void	handle_out_redir(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	int	fd;

	fd = open(redir->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			print_and_set_error(mini, redir, \
				"Minishell: %s: Permission denied.\n", 126);
		else if (errno == EISDIR)
			print_and_set_error(mini, redir, \
				"Minishell: %s: Is a directory.\n", 126);
		else if (errno == ENOENT)
			print_and_set_error(mini, redir, \
				"Minishell: %s: No such file or directory.\n", 127);
		else
			print_and_set_error(mini, redir, \
				"Minishell: %s: Error opening file.\n", 1);
		clean_fd_backup(mini, cmd);
	}
	dup2_fd(mini, cmd, fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_in_redir(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	int	fd;

	fd = open(redir->name, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->name);
		free_cmd(mini, cmd);
		free_mini(mini);
		exit(EXIT_FAILURE);
	}
	dup2_fd(mini, cmd, fd, STDIN_FILENO);
	close(fd);
}

void	setup_redirections(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redir_amount)
	{
		if (cmd->redir[i].type == HERE_DOC)
			handle_heredoc_redir(mini, cmd, &cmd->redir[i]);
		else if (cmd->redir[i].type == IN_REDIR)
			handle_in_redir(mini, cmd, &cmd->redir[i]);
		else if (cmd->redir[i].type == OUT_REDIR)
			handle_out_redir(mini, cmd, &cmd->redir[i]);
		else if (cmd->redir[i].type == OUT_APPEND)
			handle_out_append(mini, cmd, &cmd->redir[i]);
		i++;
	}
}
