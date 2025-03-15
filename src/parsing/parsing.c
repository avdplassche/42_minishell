
#include "../../includes/minishell.h"


void	free_cmd(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < mini->cmd_amount)
	{
		if (cmd[i].command != NULL)
			free(cmd[i].command);
		if (cmd[i].path != NULL)
			free(cmd[i].path);
		if (cmd[i].args != NULL)
			free_double_pointer(cmd[i].args);
	}
	free(cmd);
	cmd = NULL;
}

/** Initialize command tokens
 * @param mini t_mini containing the amount of comands in the current line
 * @param cmd command structure
 * @param i index of the cmd structure
 *
 */
void	init_cmd(t_cmd *cmd, int i)   //change it to void ?
{
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->redir = NULL;
	cmd->arg_amount = 0;
	cmd->redir_amount = 0;
	cmd->id = i + 1;
	cmd->type = -1;
}

int	is_valid_command(t_mini *mini)
{
	// int	err_char;


	if (!(is_valid_quote(mini)))
		return (printf("minishell: quote error\n") , 0); //maybe checking valid quote is a bit obsolete ?
	if (!is_valid_pipes(mini))
		return (0);
	if (!is_valid_redirections(mini))
		return (0);
	// if (err_char == UNEXPECTED_IN_REDIR)
	// 	return (printf("error near unexpected token `>>'\n"), 0);
	// else if (err_char == UNEXPECTED_OUT_REDIR)
	// 	return (printf("error near unexpected token `<<'\n"), 0);
	return (1);
}

int	set_return_value(t_mini *mini, int value)
{
	mini->last_return = value;
	if (value == 127)  //when to return (1) ?
		return (-1);
	return (0);
}

int	parsing(t_mini *mini, t_cmd *cmd)
{
	int		i;

	i = -1;
	if (!(is_valid_command(mini)))
		return (set_return_value(mini, 127));
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * mini->cmd_amount);
	if (!cmd)
		return (MALLOC_ERR);
	while (++i < mini->cmd_amount)
	{
		init_cmd(&cmd[i], i);
		fill_cmd_structure(mini, &cmd[i]);
	}


	/* EXECUTION */
	exec_mini(mini, cmd);

	if (DEBUGG_PARSING == 1)
		debug_parsing_print(mini, cmd);
	free_cmd(mini, cmd);
	return (0);
}


