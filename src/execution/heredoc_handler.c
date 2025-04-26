/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:59:03 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 20:32:49 by jrandet          ###   ########.fr       */
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
	DEBUG("HEREDOC PARENT: hd_pipe.read fd is worth %d\n", hd_p.read);
	DEBUG("HEREDOC PARENT: hd_pipe.write fd is worth %d\n", hd_p.write);
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
	close(hd_pipe.read - 1);
	hd_pipe.read = -1;
	DEBUG("HEREDOC CHILD pid is worth in heredoc: %d\n", getpid());
	get_heredoc_imput_in_pipe(mini, hd_pipe.write, redir);
	close(hd_pipe.write);
	hd_pipe.write = -1;
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
	DEBUG("HEREDOC CHILD:hd_pipe.read fd is worth %d\n", hd_pipe.read);
	DEBUG("HEREDOC CHILD: hd_pipe.write fd is worth %d\n", hd_pipe.write);
	pid = fork();
	if (pid == 0)
	{
		DEBUG("HEREDOC CHILD pid is worth in heredoc: %d\n", getpid());
		signal_child();
		heredoc_child(mini, hd_pipe, redir);
	}
	heredoc_parent(mini, hd_pipe, &pid, redir);
}

void	handle_heredoc(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = 0;
	DEBUG("HEREDOC pid is worth in heredoc: %d\n", getpid());
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
