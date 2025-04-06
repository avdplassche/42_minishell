
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

static void	setup_child_redirections(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	int	i;
	
	if (cmd_index > 0)
	{
		dup2_fd(mini, cmd, mini->pipes[cmd_index - 1].read, STDIN_FILENO);
	}
	if (cmd_index < mini->cmd_count - 1)
	{
		dup2_fd(mini, cmd, mini->pipes[cmd_index].write, STDOUT_FILENO);
	}
	i = 0;
	while (i < mini->cmd_count - 1)
	{ 
		close(mini->pipes[i].read);
		close(mini->pipes[i].write);
		i++;
	}
}

void	create_args_array(t_mini *mini, t_cmd *cmd)
{
	cmd->args = (char **)malloc(sizeof(char *) * 2);
	if (!cmd->args)
	{
		mini->last_return = MALLOC_ERROR;
		exit(EXIT_FAILURE);
	}
	cmd->args[0] = ft_strdup(cmd->command);
	cmd->args[1] = NULL;
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
	if (pid == 0)
	{
		handle_heredoc(mini, cmd);
		setup_child_redirections(mini, cmd, cmd_index);
		if (cmd->redir_amount > 0)
		{
			setup_redirections(mini, cmd);
		}
		if (cmd->type == BUILTIN)
		{
			f = get_builtin_function(cmd->command);
			f(mini, cmd);
			exit(EXIT_SUCCESS);
		}
		if (!cmd->args)
		{
			create_args_array(mini, cmd);
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

	mini->pipes = ft_calloc((mini->cmd_count - 1), sizeof(*(mini->pipes)));
	if (!mini->pipes)
	{
		mini->last_return = MALLOC_ERROR;
		exit_minishell(mini, cmd);
	}
	i = 0;
	while (i < mini->cmd_count - 1)
	{
		if (pipe(mini->pipes[i].fildes) == -1)
		{
			mini->last_return = MALLOC_ERROR;
			exit_minishell(mini, cmd);
		}
		cmd[i].pipe_out = &mini->pipes[i];
		cmd[i + 1].pipe_in = &mini->pipes[i];
		i++;
	}
}

void	set_and_execute_pipeline(t_mini *mini, t_cmd *cmd)
{
	int	cmd_index;

	cmd_index = 0;
	create_pipes(mini, cmd);
	DEBUG("entered the create pipes\n");
	while (cmd_index < mini->cmd_count)
	{
		DEBUG("entered the loop fir execute_piped_command\n");
		execute_piped_command(mini, &cmd[cmd_index], cmd_index);
		cmd_index++;
	}
	parent_closes_all_pipes(mini);
	wait_for_children(mini, cmd);
}
