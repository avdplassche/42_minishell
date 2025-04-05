
#include "minishell.h"

static void	handle_out_append(t_cmd *cmd, int *fd, int *i)
{
	*fd = open(cmd->redir[*i].pathname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

static void	handle_out_redir(t_cmd *cmd, int *fd, int *i)
{
	*fd = open(cmd->redir[*i].pathname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

static void	handle_in_redir(t_cmd *cmd, int *fd, int *i)
{
	*fd = open(cmd->redir[*i].pathname, O_RDONLY);
	if (*fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(*fd, STDIN_FILENO);
	close(*fd);
}

void	setup_redirections(t_mini *mini, t_cmd *cmd)
{
	int	fd;
	int	i;

	i = 0;
	(void)mini; //need to take this away
	while (i < cmd->redir_amount)
	{
		if (cmd->redir[i].type == IN_REDIR)
		{
			DEBUG("1\n");
			handle_in_redir(cmd, &fd, &i);
		}
		if(cmd->redir[i].type == OUT_REDIR)
		{
			DEBUG("2\n");
			handle_out_redir(cmd, &fd, &i);
		}
		if(cmd->redir[i].type == OUT_APPEND)
		{
			DEBUG("3\n");
			handle_out_append(cmd, &fd, &i);
		}
		i++;
	}
}
