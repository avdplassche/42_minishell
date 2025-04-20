/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:51:09 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/20 11:44:26 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_elements_up(char ***cursor)
{
	char	**shift;

	shift = *cursor;
	while (*shift)
	{
		*shift = *(shift + 1);
		shift++;
	}
}

static void	search_and_shrink(t_mini *mini, char **args_cursor)
{
	char	*identifier;
	char	**cursor;

	while (*args_cursor)
	{
		identifier = extract_identifier(mini, *args_cursor);
		if (ft_strcmp(identifier, "PATH") == 0)
			free_string_array(&mini->paths);
		if (!identifier)
			continue ;
		cursor = mini->envp;
		while(*cursor)
		{
			if (start_with_identifier(*cursor, identifier))
			{
				free(*cursor);
				shift_elements_up(&cursor);
				break;
			}
			cursor++;
		}
		free(identifier);
		args_cursor++;
	}
}

int builtin_unset(t_mini *mini, t_cmd *cmd)
{
	char	**args_cursor;

	if (cmd->args == 0)
		mini->last_return = 0;
	args_cursor = (cmd->args + 1);
	search_and_shrink(mini, args_cursor);
	return (mini->last_return);
}
