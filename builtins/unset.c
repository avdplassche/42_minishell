/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:51:09 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/17 13:36:53 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	search_and_shrink(t_mini *mini, char **args_cursor)
{
	char	*identifier;
	char	**cursor;

	while (*args_cursor)
	{
		cursor = mini->envp;
		identifier = extract_identifier(mini, *args_cursor);
		while(*cursor)
		{
			if (start_with_identifier(*cursor, identifier))
			{
				free(identifier);
				free(*cursor);
				*cursor = *(cursor + 1);
				break;
			}
			cursor++;
		}
		while (*cursor)
		{
			*cursor = *(cursor + 1);
			cursor++;
		}
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
