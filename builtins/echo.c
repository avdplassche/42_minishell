
#include "../includes/minishell.h"

static void	print_echo(t_cmd *cmd, int i)
{
	while(cmd->args[i])
	{
		printf("%s\n", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
}

int	builtin_echo(t_cmd *cmd)
{
	if (cmd->echo_n_index)
	{
		print_echo(cmd, cmd->echo_n_index);
		return (0);
	}
	print_echo(cmd, 1);
	printf("\n");
	return (1);
}
