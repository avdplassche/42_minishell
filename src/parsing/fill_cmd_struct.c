

#include "../../includes/minishell.h"


int	fill_cmd_bin(char *command_line, t_cmd *cmd_struct)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_space(command_line[i]))
		i++;
	while (command_line[i] && !(is_space(command_line[i])))
	{
		i++;
		j++;
	}
	cmd_struct->bin = ft_substr(command_line, i - j, j);
	return (0);
}


/**
 * Fill cmd_struct
 * @param cmd_struct an empty structure that the function will fill
 * @param bin_count number of structures, used to malloc
 * @return A cmd filled structure
 */
int	fill_cmd_structure(t_mini *mini, t_cmd *cmd_struct, int bin_count)
{
	int	i;

	i = -1;
	while (++i < bin_count)
	{
		fill_cmd_bin(mini->current_line, cmd_struct);
		// cmd_struct->builtins = test_bin(cmd_struct->bin); // 1 pour oui, 0 pour non, -1 pour inex
		// if (cmd_struct->builtins == -1)
		// 	error();
		// cmd_struct->arg = fill_cmd_arg(cmd_struct);
		// cmd_struct->fd_path = fill_cmd_fd_path(cmd_struct);
	}
	// cmd_struct = fill_cmd_booleans(cmd_struct);
	return (0);
}
