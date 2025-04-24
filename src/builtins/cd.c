/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:26:41 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/24 10:05:01 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_directory(t_mini *mini, char *path)
{
	if (chdir(path) == 0)
	{
		if (update_old_pwd_env(mini) != 0 || update_pwd_env(mini, "PWD") != 0)
			return (mini->last_return);
		mini->last_return = 0;
	}
	else
	{
		print_error("Minishell: cd: %s: No such file or directory\n", path, 2);
		mini->last_return = CMD_NOT_FOUND;
	}
	return (0);
}

static int	error_cd(t_mini *mini, char	*path)
{
	if (!*path)
	{
		print_error("Minishell: cd: %s not set\n", path, 2);
		mini->last_return = 1;
		return (mini->last_return);
	}
	return (0);
}

// int	builtin_cd(t_mini *mini, t_cmd *cmd)
// {
// 	char	*path;

// 	if (cmd->arg_amount == 0 || cmd->args[1] == NULL)
// 	{
// 		if (get_path(mini, &path, "HOME") != 0)
// 			return (mini->last_return);
// 	}
// 	else if (cmd->arg_amount == 1 && cmd->args[1][0] == '-')
// 	{
// 		mini->last_return = get_path(mini, &path, "OLDPWD");
// 		printf("%s\n", path);
// 	}
// 	else if (cmd->arg_amount > 1)
// 	{
// 		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
// 		mini->last_return = CMD_NOT_FOUND;
// 		return (mini->last_return);
// 	}
// 	else
// 		path = cmd->args[1];
// 	mini->last_return = change_directory(mini, path);
// 	return (mini->last_return);
// }


int	builtin_cd(t_mini *mini, t_cmd *cmd)
{
	char	*path;

	if (cmd->arg_amount == 0 || cmd->args[1] == NULL)
	{
		path = ft_get_env(mini, cmd, "OLDPWD");
		if (!path)
			return (error_cd(mini, "OLDPWD"));
	}
	else if (cmd->arg_amount == 1 && cmd->args[1][0] == '-')
	{
		path = ft_get_env(mini, cmd, "OLDPWD");
		if (!path)
			return (error_cd(mini, "OLDPWD"));
	}
	else if (cmd->arg_amount > 1)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		mini->last_return = CMD_NOT_FOUND;
		return (mini->last_return);
	}
	else
		path = cmd->args[1];
	mini->last_return = change_directory(mini, path);
	return (mini->last_return);
}