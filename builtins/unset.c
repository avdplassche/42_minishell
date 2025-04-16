/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:51:09 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/16 19:05:10 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_unset(t_mini *mini, t_cmd *cmd)
{
	char	*identifier;
	char	**cursor;
	
	if (cmd->args == 0)
		mini->last_return = 0;
	cmd->args++;
	identifier = extract_identifier(mini, *cmd->args);
	cursor = mini->envp;
	while(*cursor)
	{
		if (start_with_identifier(*cursor, identifier))
		{
			DEBUG("found the string here\n");
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
	return (mini->last_return);
}
