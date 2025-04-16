/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:39:23 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/16 14:27:39 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_user_command(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = -1;
	if (!mini->paths)
		return (0);
	if (!access(cmd->command, X_OK))
		return (1);
	while (mini->paths[++i])
	{
		temp = ft_strjoin(mini->paths[i], "/");
		cmd->path = ft_strjoin(temp, cmd->command);
		if (!access(cmd->path, F_OK) && !access(cmd->path, X_OK))
			return (free(temp), 1);
		free(temp);
		temp = NULL;
		free(cmd->path);
		cmd->path = NULL;
	}
	return (0);
}

/** Fill cmd type token
 * @param mini t_mini structure, containing current line to work with
 * @param cmd cmd struct
 * @return - 0 (BIN) the command can be found in PATH
 * @return - 1 (BUILTIN) the command can be found in the 'builtins' dir
 * @return - -1 (INVALID) the command is not valid
*/
int	get_cmd_type(t_mini *mini, t_cmd *cmd)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(cmd->command);
	if (!(ft_strncmp(cmd->command, "echo", len)))
	{
		if (is_builtin_echo(cmd))
			return (BUILTIN);
		else
			return (is_user_command(mini, cmd), USER);
	}
	while (++i < BUILTIN_AMOUNT)
	{
		if (ft_strlen(cmd->command) < ft_strlen(mini->builtins[i]))
			len = ft_strlen(mini->builtins[i]);
		if (!(ft_strncmp(mini->builtins[i], cmd->command, len)))
			return (BUILTIN);
	}
	if (is_user_command(mini, cmd))
		return (USER);
	return (INVALID);
}
