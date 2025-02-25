/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:55:41 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/25 01:01:31 by alvan-de         ###   ########.fr       */
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
	mini.builtins = ft_split(BUILTINS, ',');
	int i = -1;
	while (mini.builtins[++i])   //create a print.c
		printf("%d : %s\n",i, mini.builtins[i]);
	while (1)
	{
		printf("\n");
		printf("Prompt minishell ⇰\n");
		mini.current_line = get_next_line(STDIN);
		/* put line in history */
		parsing(&mini);
		free(mini.current_line);
		mini.current_line = NULL;
	}



}
