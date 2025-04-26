/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:39:30 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/26 12:20:30 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/** Initialize command tokens
 * @param cmd command structure
 * @param i index of the cmd structure
 */
void	init_cmd(t_cmd *cmd, int i)
{
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->id = i + 1;
	cmd->type = -1;
}

int	is_valid_command(t_mini *mini)
{
	if (!(is_valid_quote_basckslash(mini)))
		return (0);
	if (!is_valid_pipes(mini))
		return (print_unexpected_token("|"), 0);
	if (!is_valid_redirections(mini))
		return (0);
	if (!is_valid_backslash(mini))
		return (0);
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
	if (!(is_valid_command(mini)))
		return (set_return_value(mini, 127));
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * mini->cmd_count);
	if (!cmd)
		exit_minishell(mini);
	mini->cmd = cmd;
	expand_tildes(mini);
	mini->line = dollar_handle(mini, mini->line);
	mini->line = wildcard_handle(mini, mini->line);
	if (!is_valid_syntax(mini->line))
		return (free_cmd(mini), set_return_value(mini, 2));
	while (++i < mini->cmd_count)
		cmd_fill_loop(mini, &cmd[i], i);
	DEBUG("\n-----------------------------------------------\n");
	exec_mini(mini, cmd);
	if (cmd)
	{
		free_cmd(mini);
		cmd = NULL;
	}
	mini->cursor = 0;
}
