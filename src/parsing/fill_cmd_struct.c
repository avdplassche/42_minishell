

#include "../../includes/minishell.h"


/** Used to fill the command, stops when it finds a
 * redir, a pipe or a space
 *@param cmd_line : the command line to parse
 *@param cmd_struct : the command structure to fill
 *@return not set yet (maybe error)
 */
int	fill_cmd_bin(char *cmd_line, t_cmd *cmd_struct)
{
	int	i;
	int	j;
	int	nl;

	i = 0;
	j = 0;
	while (is_space(cmd_line[i]))
		i++;
	while (cmd_line[i] && !(is_space(cmd_line[i]))
		&& !(contain_char("<>|", cmd_line[i])))
	{
		i++;
		j++;
	}
	if (contain_char("<>|", cmd_line[i])) //because of weird behaviour, maybe macos
		nl = 0;
	else
		nl = 1;
	cmd_struct->bin = ft_substr(cmd_line, i - j, j - nl);
	return (0);
}


/**
 * Fill cmd_struct
 * @param cmd_struct an empty structure that the function will fill
 * @param bin_count number of structures, used to malloc
 * @return A cmd filled structure
 */
int	fill_cmd_structure(t_mini *mini, t_cmd *cmd, int bin_count)
{
	int	i;

	i = -1;
	while (++i < bin_count)
	{
		cmd->number = i + 1;    //starting from 0 or 1 ?
		fill_cmd_bin(mini->current_line, cmd);
		// cmd_struct->builtins = test_bin(cmd_struct->bin); // 1 pour oui, 0 pour non, -1 pour inex
		// if (cmd_struct->builtins == -1)
		// 	error();
		// cmd_struct->arg = fill_cmd_arg(cmd_struct);
		// cmd_struct->fd_path = fill_cmd_fd_path(cmd_struct);
	}
	// cmd_struct = fill_cmd_booleans(cmd_struct);
	return (0);
}
