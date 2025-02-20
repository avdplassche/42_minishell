/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:55:41 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/20 02:37:41 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	printf("Prompt\n");
	// printf("- - - - - - - - - - - - - - - - - - - - - -\n");
	while (1)
	{
		cmd = malloc(sizeof(char));
		read(0, cmd, 1024);
		if (ft_strncmp(cmd, "exit", 4) == 0)
		{
			free(cmd);
			write(1, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		parsing(cmd);
	}


}
