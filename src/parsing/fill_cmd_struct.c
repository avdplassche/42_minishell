

#include "../../includes/minishell.h"

/** Fill cmd arg tokens, a char** that will be used in execve
 * @param cmd_line the command line from the prompt
 * @param cmd_struct the command structure to fill
 * @return error ? not set yet
 */
int	fill_cmd_args(t_mini *mini, t_cmd *cmd_struct)
{
	int		i;
	int		j;
	char	*arg;

	j = 0;
	i = cmd_struct->index;
	while (is_space(mini->current_line[i]) == 1)
		i++;
	j = i;
	while (mini->current_line[i] && contain_char("|<>", mini->current_line[i]))
		i++;
	arg = malloc(sizeof(char) * (i - j + 1));
	return (0);
}

/** Fill cmd type token
 * @param mini t_mini structure, containing current line to work with
 * @param cmd cmd struct
 * @return - 0 (BIN) the command can be found in PATH
 * @return - 1 (BUILTIN) the command can be found in the 'builtins' dir
 * @return - -1 (UNVALID) the command is not valid
 */
int	fill_cmd_type(t_mini *mini, t_cmd *cmd)
{
	

}


/** Fill the command token, stops when it finds a redir, a pipe or a space
 *@param cmd_line the command line from the prompt
 *@param cmd_struct the command structure to fill
 *@return not set yet (maybe error)
 */
int	fill_cmd_string(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_space(mini->current_line[i]))
		i++;
	while (mini->current_line[i] && !(is_space(mini->current_line[i]))
		&& !(contain_char("<>|", mini->current_line[i])))
	{
		i++;
		j++;
	}
	cmd->command = ft_substr(mini->current_line, i - j, j);
	cmd->index = i;
	return (0);
}

/** Fill command structure (for 1 command of the command line)
 * @param mini t_mini structure, containing current line to work with
 * @param cmd_s an empty structure that the function will fill
 * @param bin_count number of structures, used to malloc
 * @return A cmd filled structure
 */
int	fill_cmd_structure(t_mini *mini, t_cmd *cmd, int cmd_amount)
{
	int	i;

	i = -1;
	while (++i < cmd_amount)
	{
		fill_cmd_string(mini, cmd);
		if (fill_cmd_type(mini, cmd) == -1)
		{
			//error
		}
		/* FOLLOWING IS ACTUALLY FILL CMD TYPE*/

			// cmd_struct->builtins = test_bin(cmd_struct->bin); // 1 pour oui, 0 pour non, -1 pour inex
			// if (cmd_struct->builtins == -1)
			// 	error();
		if (mini->current_line[cmd->index])
			fill_cmd_args(mini, cmd);
		else
			return (0);
		// fill_cmd_fd_path(cmd);
	}
	// cmd_struct = fill_cmd_booleans(cmd_struct);
	return (0);
}
