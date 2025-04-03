
#include "minishell.h"

int	new_builtin_echo(t_mini *mini, t_cmd *cmd)
{
	int i;
	int	j;
	int takeaway_new_line;

	i = 1;
	takeaway_new_line = 0;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		j = 1;
		while (cmd->args[i] && cmd->args[i][0] == 'n')
			j++;
		if (cmd->args[i][j] == '\0')
			break;
		takeaway_new_line = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!takeaway_new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
	
