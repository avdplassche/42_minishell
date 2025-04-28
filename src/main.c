/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:40 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/28 11:34:22 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_line(t_mini *mini, char *input)
{
	mini->line = ft_strtrim(input, SPACES);
	free(input);
	str_malloc_check(mini, mini->line);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	t_cmd	*cmd;
	char	*input;

	(void)argv;
	if (init_mini(&mini, envp) == -1)
		return (EXIT_FAILURE);
	while (argc == 1)
	{
		setup_signal_handlers(&mini);
		cmd = NULL;
		input = readline("Minishell ➤ ");
		if (!input)
			break ;
		add_history(input);
		set_line(&mini, input);
		mini.cmd_count = count_cmd(&mini);
		if ((!(is_only_spaces(mini.line)) || mini.line[0] != '#')
			&& mini.line[0])
			parsing(&mini, cmd);
		free_string_ptr(&mini.line);
	}
	rl_clear_history();
	free_mini(&mini);
	DEBUG_CLOSE;
	return (mini.last_return);
}
