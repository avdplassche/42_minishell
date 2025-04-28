/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:40 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/28 12:55:16 by jrandet          ###   ########.fr       */
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
	if (argc == 2)
	{
		int script_status = execute_file(&mini, argv[1]);
		mini.last_return = script_status;
	}
	rl_clear_history();
	free_mini(&mini);
	DEBUG_CLOSE;
	return (mini.last_return);
}
