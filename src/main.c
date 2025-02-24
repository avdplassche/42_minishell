/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:55:41 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/24 16:58:44 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Function for env to be used everywhere and to iterate on its values
 * @param mini an empty t_mini_structure
 * @param envp the terminal env variable
 * @note this is for minishell to have it's own env variable
 *
 */
t_mini	dup_env(t_mini mini, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	mini.envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		mini.envp[i] = ft_strdup(envp[i]);
	mini.envp[i] = NULL;
	return (mini);
}


int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	mini = dup_env(mini, envp);
	while (1)
	{
		printf("Prompt minishell ⇰\n");
		mini.current_line = get_next_line(STDIN);
		/* put line in history */
		parsing(&mini);
		free(mini.current_line);
		mini.current_line = NULL;
	}



}
