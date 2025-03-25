
#include "minishell.h"

static void	print_echo(t_cmd *cmd, int i)
{
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i])
			printf(" ");
	}
}

int	builtin_echo(t_cmd *cmd, t_mini *mini)
{
	(void)mini;
	if (cmd->echo_n_index)
	{
		print_echo(cmd, cmd->echo_n_index);
	}
	else
	{
		print_echo(cmd, 1);
		printf("\n");
	}
	return (0);
}
