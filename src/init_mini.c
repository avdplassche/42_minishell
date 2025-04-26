/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 00:34:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 13:36:58 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** Count command amount in command line, that will be used for pipes.
 * @param mini t_mini containing the command line
 * @return number of commands
 * @note proceed by countint pipe char '|'
 */
int	count_cmd(t_mini *mini)
{
	int		i;
	int		count;
	t_quote	q;

	count = 1;
	i = -1;
	q.dbl = 0;
	q.sgl = 0;
	while (mini->line[++i])
	{
		quote_enclosure_handle(mini->line[i], &q);
		if (mini->line[i] == '|' && !q.sgl && !q.dbl)
			count++;
	}
	return (count);
}

/** Function for env to be used everywhere and to iterate on its values
 * @param mini an empty t_mini_structure
 * @param envp the terminal env variable
 * @note this is for minishell to have it's own env variable
 */
int	dup_env(t_mini *mini, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	mini->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!mini->envp)
		exit_minishell(mini);
	i = -1;
	while (envp[++i])
	{
		mini->envp[i] = ft_strdup(envp[i]);
		if (!mini->envp)
			exit_minishell(mini);
	}
	mini->envp[i] = NULL;
	return (0);
}

void	set_path(t_mini *mini)
{
	char	*env;

	env = NULL;
	if (mini->paths)
		free_string_array(&mini->paths);
	env = ft_get_env(mini, "PATH");
	if (env)
	mini->paths = ft_split(env, ':');
	{
		dbl_str_malloc_check(mini, mini->paths);
	}
	if (env)
		free(env);
}

/** Fill t_mini mini's variable
 * @param mini an empty t_mini_structure
 * @param envp the terminal env variable
 */
int	init_mini(t_mini *mini, char **envp)
{
	ft_bzero(mini, sizeof(*mini));
	if (BUILTINS_STRING)
		mini->builtins = ft_split(BUILTINS_STRING, ',');
	if (!mini->builtins)
		exit_minishell(mini);
	mini->last_return = 0;
	if (envp[0])
		dup_env(mini, envp);
	else
		mini->envp = NULL;
	set_path(mini);
	mini->stdin_backup = -1;
	mini->stdout_backup = -1;
	mini->should_exit = false;
	mini->cursor = 0;
	return (0);
}
