/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:01:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/22 18:02:08 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** Frees char ** variables
*/
void	free_string_array(char ***array)
{
	int	i;

	i = 0;
	if (!array || !(*array))
		return ;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

void	free_pathnames(t_cmd *cmd)
{
	int	i;

	if (!(cmd->redir))
		return ;
	i = 0;
	while (i < cmd->redir_amount)
	{
		free(cmd->redir[i].name);
		i++;
	}
	free(cmd->redir);
	cmd->redir = NULL;
}
