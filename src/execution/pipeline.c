
#include "minishell.h"

static void	parent_closes_all_pipes(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->cmd_count - 1)
	{
		close(mini->pipes[i].read);
		close(mini->pipes[i].write);
		i++;
	}
	free(mini->pipes);
	mini->pipes = NULL;
}

static void	setup_child_redirections(t_mini *mini, int cmd_index)
{
	int	i;
	
	if (cmd_index > 0)
	{ // stdin is connected to the read end of the previous pipe
		dup2(mini->pipes[cmd_index - 1].read, STDIN_FILENO); //if not the first command, redirects its input to the previous pipe ls |(this pipe) grep | wc 
	} //if i am the first command, i only look at the line below 
	if (cmd_index < mini->cmd_count - 1) //in both these cases it is the middle command 
	{ //stdout is connected to the write end of the next pipe
		dup2(mini->pipes[cmd_index].write, STDOUT_FILENO); // if not the last command, redirects its output to the next pipe ls | grep |(this pipe) wc
	} //if i am the last command, i only look at the first if.
	i = 0;
	while (i < mini->cmd_count - 1)
	{ //all original file descriptors closed as they have either been duplicated or 
		close(mini->pipes[i].read);
		close(mini->pipes[i].write);
		i++;
	}
}

static void	execute_piped_command(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	pid_t 			pid;
	t_builtin_func	f;

	pid = fork();
	if (pid == -1)
	{
		mini->last_return = MALLOC_ERROR;
		exit(EXIT_FAILURE);
	}
	if (pid == 0) //inside the child process 
	{
		setup_child_redirections(mini, cmd_index);
		if (cmd->redir_amount > 0)
		{
			setup_redirections(mini, cmd);
		}
		if (cmd[cmd_index].redir->type == BUILTIN)
		{
			f = get_builtin_function(cmd->command);
			f(mini, cmd);
		}
		if (execve(cmd->path, cmd->args, mini->envp) == -1)
		{
			perror("execve");
			mini->last_return = MALLOC_ERROR;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cmd->pid = pid;
	}
}
static void	create_pipes(t_mini *mini, t_cmd *cmd)
{
	int			i;
	t_pipefd	*p;

	mini->pipes = ft_calloc((mini->cmd_count - 1), sizeof(*(mini->pipes)));
	if (!mini->pipes)
	{
		mini->last_return = MALLOC_ERROR;
		minishell_exit(mini, cmd);
	}
	p = mini->pipes;
	i = 0;
	while (i < mini->cmd_count -1)
	{
		if (pipe(p[i].fildes) == -1)
		{
			mini->last_return = MALLOC_ERROR;
			minishell_exit(mini, cmd);
		}
		cmd[i].pipe_out = &mini->pipes[i]; // ls | this is the first pipe
		cmd[i + 1].pipe_in = &mini->pipes[i]; // the next commmand's pipe in is the same pipe shared. 
		i++;
	}
}

void	set_and_execute_pipeline(t_mini *mini, t_cmd *cmd)
{
	int	cmd_index;

	cmd_index = 0;
	if (cmd->redir[0].type == HERE_DOC)
	{
		mini->cmd_count += 1;
	}
	create_pipes(mini, cmd);
	while (cmd_index < mini->cmd_count)
	{
		if (cmd->redir[0].type == HERE_DOC)
		{
			handle_heredoc(mini, cmd);
		}
		execute_piped_command(mini, &cmd[cmd_index], cmd_index);
		cmd_index++;
	}
	parent_closes_all_pipes(mini);
	wait_for_children(mini, cmd);
}
