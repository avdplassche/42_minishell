
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
	
	if (cmd->pipe_in_heredoc_read_fd != -1)
	{
		DEBUG("setting the herecoc pipe fd %d for command\n", cmd->pipe_in_heredoc_read_fd);
		if(dup2(cmd->pipe_in_heredoc_read_fd, STDIN_FILENO) == -1)  // Fixed semicolon here
			perror("dup2 heredoc");
		close(cmd->pipe_in_heredoc_read_fd);
	}
	if (cmd_index > 0)
	{
		if(dup2(mini->pipes[cmd_index - 1].read, STDIN_FILENO) == -1)  // Added error check
			perror("dup2 stdin");
	}
	if (cmd_index < mini->cmd_count - 1)
	{
		if(dup2(mini->pipes[cmd_index].write, STDOUT_FILENO) == -1)  // Added error check
			perror("dup2 stdout");
	}
	i = 0;
	while (i < mini->cmd_count - 1)
	{ 
		close(mini->pipes[i].read);
		close(mini->pipes[i].write);
		i++;
	}
}

static void	execute_piped_command(t_mini *mini, t_cmd *cmd, int cmd_index)
{
	pid_t 			pid;
	t_builtin_func	f;

	DEBUG("DEBUG: Command at index %d: '%s'\n", cmd_index, cmd->command ? cmd->command : "NULL");
	DEBUG("DEBUG: Args pointer: %p\n", (void*)cmd->args);
	// Only try to print args if the pointer is not NULL
	if (cmd->args) {
	DEBUG("DEBUG: First arg: %s\n", cmd->args[0] ? cmd->args[0] : "NULL");
	DEBUG("DEBUG: Arg count: %d\n", cmd->arg_amount);
}

	pid = fork();
	if (pid == -1)
	{
		mini->last_return = MALLOC_ERROR;
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_child_redirections(mini, cmd, cmd_index);
		if (cmd->redir_amount > 0 && cmd->redir[0].type != HERE_DOC)
		{
			DEBUG("entered loop where redir amount is above 0\n");
			setup_redirections(mini, cmd);
		}
		if (cmd->type == BUILTIN)
		{
			DEBUG("in execute piped command entered the BUILTIN\n");
			f = get_builtin_function(cmd->command);
			f(mini, cmd);
			exit(EXIT_SUCCESS);
		}
		if (cmd->type == USER) {
			DEBUG("DEBUG: About to execute '%s'\n", cmd->path);
			DEBUG("DEBUG: Arguments list:\n");
			int i = 0;
			while (cmd->args[i]) {
				DEBUG( "DEBUG: arg[%d] = '%s'\n", i, cmd->args[i]);
				i++;
			}
			
			// Check if stdin is correctly set to the heredoc fd
			int stdin_fd = fcntl(STDIN_FILENO, F_GETFD);
			DEBUG( "DEBUG: Current stdin fd status: %d\n", stdin_fd);
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
			perror("pipe creation");
			mini->last_return = MALLOC_ERROR;
			exit_minishell(mini, cmd);
		}
		cmd[i].pipe_out = &mini->pipes[i];
		cmd[i + 1].pipe_in = &mini->pipes[i];
		i++;
	}
}
/// @brief 
/// @param mini 
/// @param cmd 
void	set_and_execute_pipeline(t_mini *mini, t_cmd *cmd)
{
	int	pid;
	int	cmd_index;
	int	i;
	int	status;

	cmd_index = 0;
	i = 0;
	while (cmd_index < mini->cmd_count) // count the number of heredocs in this implementation
	{
		while (i < cmd[cmd_index].redir_amount)
		{
			if (cmd[cmd_index].redir[i].type == HERE_DOC)
			{
				pid = handle_heredoc(mini, &cmd[cmd_index]);
				waitpid(pid, &status, 0);
			}
			i++;
		}
		cmd_index++;
	}
	cmd_index = 0;
	create_pipes(mini, cmd);
	while (cmd_index < mini->cmd_count)
	{
		DEBUG("entered the loop fir execute_piped_command\n");
		execute_piped_command(mini, &cmd[cmd_index], cmd_index);
		cmd_index++;
	}
	parent_closes_all_pipes(mini);
	wait_for_children(mini, cmd);
}
