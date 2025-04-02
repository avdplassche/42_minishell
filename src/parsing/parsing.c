
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
	if (!(is_valid_quote(mini)))
		return (DEBUG("minishell: quote error\n"), 0);
	if (!is_valid_pipes(mini))
		return (0);
	if (!is_valid_redirections(mini))
		return (0);
	if (!is_valid_backslash(mini))
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
	if (value == 127)
		return (-1);
	return (0);
}

void	cmd_fill_loop(t_mini *mini, t_cmd *cmd, int i)
{
	init_cmd(cmd, i);
	fill_cmd_structure(mini, cmd);
	if (mini->line[mini->cursor] == '|')
	{
		mini->cursor++;
		while (mini->line[mini->cursor]
			&& mini->line[mini->cursor] == ' ')
			mini->cursor++;
	}
	print_cmd(*cmd, mini->line);
}

int	parsing(t_mini *mini, t_cmd *cmd)
{
	int		i;

	i = -1;
	if (!(is_valid_command(mini)))
		return (set_return_value(mini, 127));
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * mini->cmd_count);
	if (!cmd)
		exit_minishell(mini, cmd);
	expand_tildes(mini);
	mini->line = dollar_handle(mini, mini->line);
	mini->line = wildcard_handle(mini->line);
	while (++i < mini->cmd_count)
		cmd_fill_loop(mini, &cmd[i], i);
	DEBUG("\n-----------------------------------------------\n");
	// exec_mini(mini, cmd);
	if (!mini->should_exit)
		free_cmd(mini, cmd);
	cmd = NULL;
	return (mini->last_return);
}
