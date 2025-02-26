

#include "../../includes/minishell.h"

/** Fill cmd arg tokens, a char** that will be used in execve
 * @param cmd_line the command line from the prompt
 * @param cmd_struct the command structure to fill
 * @return error ? not set yet
 */
int	fill_cmd_args(char *cmd_line, t_cmd *cmd_struct)
{
	int		i;
	int		j;
	char	*arg;

	j = 0;
	i = cmd_struct->index;
	while (is_space(cmd_line[i]) == 1)
		i++;
	j = i;
	while (cmd_line[i] && contain_char("|<>", cmd_line[i]))
		i++;
	arg = malloc(sizeof(char) * (i - j + 1));
	return (0);
}

/** Used to fill the command, stops when it finds a
 * redir, a pipe or a space
 *@param cmd_line the command line from the prompt
 *@param cmd_struct the command structure to fill
 *@return not set yet (maybe error)
 */
int	fill_cmd_bin(char *cmd_line, t_cmd *cmd_s)
{
	int	i;
	int	j;

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
	cmd_s->bin = ft_substr(cmd_line, i - j, j);
	cmd_s->index = i;
	return (0);
}


/** Fill command structure, that will be executed
 * @param cmd_s an empty structure that the function will fill
 * @param bin_count number of structures, used to malloc
 * @return A cmd filled structure
 */
int	fill_cmd_structure(t_mini *mini, t_cmd *cmd_s, int bin_count)
{
	int	i;

	i = -1;
	while (++i < bin_count)
	{
		fill_cmd_bin(mini->current_line, cmd_s);
		// cmd_struct->builtins = test_bin(cmd_struct->bin); // 1 pour oui, 0 pour non, -1 pour inex
		// if (cmd_struct->builtins == -1)
		// 	error();
		if (mini->current_line[cmd_s->index])
			fill_cmd_args(mini->current_line, cmd_s);
		else
			return (0);
		// fill_cmd_fd_path(cmd);
	}
	// cmd_struct = fill_cmd_booleans(cmd_struct);
	return (0);
}
