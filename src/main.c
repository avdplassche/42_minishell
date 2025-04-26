/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:40 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 19:18:26 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// void	loop_3args(char **argv, t_mini mini, t_cmd *cmd)
// {
// 	int fd = open(argv[1], O_RDONLY);
// 	char buffer[10000];
// 	int c = 0;
// 	int r = read(fd, buffer, 9999);
// 	char	*next_line = NULL;

// 	cmd = NULL;
// 	buffer[r] = '\0';
// 	close(fd);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 		perror("error");
// 	while (TEST_MODE == 1 && c < ft_atoi(argv[2]))
// 	{
// 		next_line = get_next_line(fd);
// 		mini.line = ft_strtrim(next_line, SPACES);
// 		free(next_line);
// 		mini.cmd_count = count_cmd(&mini);
// 		mini.cursor = 0;
// 		DEBUG("\nCOMMAND LINE %d ➤ %s¶\n\n", c + 1, mini.line);
// 		if (!(is_only_spaces(mini.line)) || mini.line[0] != '#')
// 			parsing(&mini, cmd);
// 		free(cmd);
// 		free(mini.line);
// 		mini.line = NULL;
// 		c++;
// 	}
// 	close(fd);
// }

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
