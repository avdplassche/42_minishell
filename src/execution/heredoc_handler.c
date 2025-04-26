/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:59:03 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 17:16:42 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_parent(t_mini *mini, t_pipefd hd_p, int *pid, t_redir *red)
{
	int		wstatus;

	close(hd_p.write);
	hd_p.write = -1;
	red->heredoc_fd = hd_p.read;
	waitpid(*pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGINT)
		{
			write(1, "\n", 1);
			mini->last_return = 130;
		}
	}
}

static void	heredoc_child(t_mini *mini, t_pipefd hd_pipe, t_redir *redir)
{
	close(hd_pipe.read);
	hd_pipe.read = -1;
	get_heredoc_imput_in_pipe(mini, hd_pipe.write, redir);
	close(hd_pipe.write);
	exit_minishell(mini);
}

static void	create_heredoc_process(t_mini *mini, t_redir *redir)
{
	pid_t		pid;
	t_pipefd	hd_pipe;

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
	heredoc_parent(mini, hd_pipe, &pid, redir);
}

void	handle_heredoc(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	setup_command_signal(mini);
	while (i < cmd->redir_amount)
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
