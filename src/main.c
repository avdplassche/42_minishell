/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:55:41 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/23 19:28:08 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



/**
 * Function for env to be used everywhere and to iterate on its values
 * @note
 *
 *
 *
 */
t_mini	dup_env(t_mini mini, char **envp)
{



}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	mini;

	mini = fill_env(mini, envp);
	printf("\n");
	while (1)
	{
		printf("Prompt minishell ⇰\n");
		line = get_next_line(STDIN);
		//put line in history
		parsing(line);

		free(line);
		line = NULL;
	}



}
