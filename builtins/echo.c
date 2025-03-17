
#include "../includes/minishell.h"


// int	echo(t_cmd *cmd)
// {
// 	int	i;
// 	int	is_option_n;

// 	is_option_n = 0;
// 	if (cmd->args[1] && (ft_strcmp(cmd->args[1], "-n") == 0))
// 	{
// 		is_option_n = 1;
// 		i = 2;
// 	}
// 	while (cmd->args[i])
// 	{
// 		printf("%s\n", cmd->args[i]);
// 		if (cmd->args[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	if (!is_option_n)
// 		printf("\n");
// 	return (0);
// }