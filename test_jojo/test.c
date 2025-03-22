/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 10:39:05 by jrandet           #+#    #+#             */
/*   Updated: 2025/03/22 10:54:49 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	string_array_replace(t_mini *mini, char	*env_key, char *path_replace)
{
	int	i;

	i = 0;
	while (mini->envp[i])
	{
		if (start_with(mini->envp[i], env_key))
		{
			free(mini->envp[i]);
			mini->envp[i] = path_replace;
			printf("full path rteplacement is %s and the mini->envp[i] is %s\n", path_replace, mini->envp[i]);
			free(path_replace);
			return ;
		}
		i++;
	}
}

static char	*get_new_path(t_mini *mini, char *env_key, char *new_path)
{
	char	*full_new_path;
	
	full_new_path = malloc((ft_strlen(env_key) + ft_strlen(new_path) + 1));
	if (!full_new_path)
	{
		mini->last_return = MALLOC_ERROR;
		free(new_path);
		return (NULL);
	}
	string_build(&full_new_path, env_key, new_path);
	printf("in get_new_path, full new path is %s\n");
	return (full_new_path);
}

char	*get_current_workdir(void)
{
	char	buffer[PATH_MAX + 1];
	char	*new_cwd;
	
	new_cwd = getcwd(buffer, PATH_MAX + 1);
	if (!new_cwd_path)
	{
		mini->last_return = MALLOC_ERROR;
		return (NULL);
	}
	return (new_cwd);
}

void	update_pwd_env(t_mini *mini, t_cmd *cmd, char *env_var)
{
	char	*old_pwd_path;
	char	*full_new_path;
	char	*env_key_variable;
	char	*new_cwd;
	(void)cmd;
	
	env_key_variable = string_array_create_key(env_var, ft_strlen(env_var));
	new_cwd = get_current_workdir();
	full_new_path = get_new_path(mini, env_key_variable, new_cwd); //find the path of the new working directory
	old_pwd_path = string_array_find_string(mini->envp, env_var);
	//if (!old_pwd_path)
	//{
		//string_array_push(mini, cmd, full_new_path);
	//}
	string_array_replace(mini, env_key_variable);
}

int main(int argc, char **argv, char **env)
{
	t_mini	mini;
	t_cmd	cmd;
	
	(void)argc;
	(void)argv;
	
	mini.envp = env;
	update_pwd(&mini, &cmd, "PWD");
	return (0);
}



//replace_old_pwd(mini, old_pwd); separate function !!!

/*

HEAP : FULL_PATH_REPLACEMENT using this space in the heap for my program, need to free it afterwards
do not forget to free


*/