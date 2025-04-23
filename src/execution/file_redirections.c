/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:57:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/23 22:00:50 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_redir(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	if (redir->heredoc_fd != -1)
	{
		if (redir->heredoc_fd == STDIN_FILENO)
			return ;
		dup2_fd(mini, cmd, redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
	}
}

static int	handle_out_append(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	int	fd;

	fd = open(redir->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			print_error("Minishell: %s: Permission denied\n", redir->name, 2);
		else if (errno == EISDIR)
			print_error("Minishell: %s: Is a directory\n", redir->name, 2);
		else if (errno == ENOENT)
			print_error("Minishell: %s: No such file or directory\n", \
				redir->name, 2);
		else
			print_error("Minishell: %s: Error opening file\n", redir->name, 2);
		mini->last_return = 1;
		return (1);
	}
	dup2_fd(mini, cmd, fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_out_redir(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	int	fd;

	fd = open(redir->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			print_error("Minishell: %s: Permission denied\n", redir->name, 2);
		else if (errno == EISDIR)
			print_error("Minishell: %s: Is a directory\n", redir->name, 2);
		else if (errno == ENOENT)
			print_error("Minishell: %s: No such file or directory\n", \
				redir->name, 2);
		else
			print_error("Minishell: %s: Error opening file\n", redir->name, 2);
		mini->last_return = 1;
		return (1);
	}
	dup2_fd(mini, cmd, fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_in_redir(t_mini *mini, t_cmd *cmd, t_redir *redir)
{
	int	fd;

	fd = open(redir->name, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			print_error("Minishell: %s: Permission denied\n", redir->name, 2);
		else if (errno == EISDIR)
			print_error("%s: read failed: -: Is a directory\n", redir->name, 2);
		else if (errno == ENOENT)
			print_error("Minishell: %s: No such file or directory\n", \
				redir->name, 2);
		else
			print_error("Minishell: %s: Error opening file\n", redir->name, 2);
		mini->last_return = 1;
		return (1);
	}
	dup2_fd(mini, cmd, fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	setup_command_redirections(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < cmd->redir_amount)
	{
		if (cmd->redir[i].type == HERE_DOC)
			handle_heredoc_redir(mini, cmd, &cmd->redir[i]);
		else if (cmd->redir[i].type == IN_REDIR)
			result = handle_in_redir(mini, cmd, &cmd->redir[i]);
		else if (cmd->redir[i].type == OUT_REDIR)
			result = handle_out_redir(mini, cmd, &cmd->redir[i]);
		else if (cmd->redir[i].type == OUT_APPEND)
			result = handle_out_append(mini, cmd, &cmd->redir[i]);
		if (result != 0)
			break ;
		i++;
	}
	return (result);
}
