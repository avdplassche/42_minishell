
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
		return (print_error("minishell: quote error\n", NULL, 2), 0);
	if (!is_valid_pipes(mini))
		return (print_unexpected_token("|"), 0);
	if (!is_valid_redirections(mini))
		return (0);
	// if (!is_valid_backslash(mini))
	// 	return (0);
	// if (err_char == UNEXPECTED_IN_REDIR)
	// 	return (printf("error near unexpected token `>>'\n"), 0);
	// else if (err_char == UNEXPECTED_OUT_REDIR)
	// 	return (printf("error near unexpected token `<<'\n"), 0);
	return (1);
}

void	set_return_value(t_mini *mini, int value)
{
	mini->last_return = value;
}

void	cmd_fill_loop(t_mini *mini, t_cmd *cmd, int i)
{
	init_cmd(cmd, i);
	fill_cmd_structure(mini, cmd);
	cmd->is_directory = is_directory(cmd->command);
	print_cmd(*cmd, mini->line);
	if (mini->line[mini->cursor] == '|')
	{
		mini->cursor++;
		while (mini->line[mini->cursor]
			&& mini->line[mini->cursor] == ' ')
			mini->cursor++;
	}
}

void	parsing(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (is_only_specific_char(mini->line, '%'))
		return (print_error("minishell: fg: %s: no such job\n", mini->line, 2)
			, set_return_value(mini, 2));
	if (!(is_valid_command(mini)))
		return (set_return_value(mini, 127));
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * mini->cmd_count);
	if (!cmd)
		exit_minishell(mini, cmd);
	mini->cmd = cmd;
	expand_tildes(mini);
	mini->line = dollar_handle(mini, mini->line);
	mini->line = wildcard_handle(mini, mini->line);
	while (++i < mini->cmd_count)
	{
		cmd_fill_loop(mini, &cmd[i], i);
		if (!is_valid_syntax(cmd[i].command))
			return (free_cmd(mini, cmd), set_return_value(mini, 2));
	}
	DEBUG("\n-----------------------------------------------\n");
	// exec_mini(mini, cmd);
	free_cmd(mini, cmd);
}
