
#include "minishell.h"


/** Initialize command tokens
 * @param cmd command structure
 * @param i index of the cmd structure
 */
void	init_cmd(t_cmd *cmd, int i)
{
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->redir = NULL;
	cmd->arg_amount = 0;
	cmd->redir_amount = 0;
	cmd->id = i + 1;
	cmd->echo_n_index = 0;
	cmd->type = -1;
}

int	is_valid_command(t_mini *mini)
{
	// int	err_char;


	if (!(is_valid_quote(mini)))
		return (printf("minishell: quote error\n---------------------------\n") , 0);
	if (!is_valid_pipes(mini))
		return (0);
	if (!is_valid_redirections(mini))
		return (0);
	if	(!is_valid_arithmetic(mini))
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
		return (MALLOC_ERROR);
	while (++i < mini->cmd_amount)
	{
		init_cmd(&cmd[i], i);
		fill_cmd_structure(mini, &cmd[i]);
		if (mini->line[mini->cursor] == '|')
		{
			mini->cursor++;
			while (mini->line[++mini->cursor]
				&& mini->line[mini->cursor] == ' ')
				mini->cursor++;
		}
	}
	debug_parsing_print(mini, cmd);
	/* EXECUTION */
	// exec_mini(mini, cmd);
	free_cmd(mini, cmd);
	return (0);
}

// int	get_function_pointer()
// {



// }
