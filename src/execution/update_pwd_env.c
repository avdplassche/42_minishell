
#include "minishell.h"

static void handle_error(t_mini *mini, char *env_key)
{
	free(env_key);
	mini->last_return = MALLOC_ERROR;
}

int	update_pwd_env(t_mini *mini, char *env_var)
{
	char	*env_row;
	char	*env_key;
	char	*new_cwd;
	
	env_key = string_array_create_key(env_var, ft_strlen(env_var));
	if (!env_key)
		return (mini->last_return = MALLOC_ERROR);
	new_cwd = get_current_workdir(mini);
	if (!new_cwd)
	{
		handle_error(mini, env_key);
		return (mini->last_return);
	}
	env_row = get_new_env_row(mini, env_key, new_cwd);
	if (!env_row)
	{
		handle_error(mini, env_key);
		return (mini->last_return);
	}
	set_env(mini, env_key, env_row);
	free(env_key);
	free(new_cwd);
	mini->last_return = 0;
	return (mini->last_return);
}

int	update_old_pwd_env(t_mini *mini)
{
	char	*env_row;
	char	*env_key;
	char	*original_pwd;

	original_pwd = ft_get_env(mini, "PWD");
	if (!original_pwd)
	{
		original_pwd = get_current_workdir(mini);
		if (!original_pwd)
			mini->last_return = MALLOC_ERROR;
	}
	else
	{
		original_pwd = ft_strdup(original_pwd);
		if (!original_pwd)
			mini->last_return = MALLOC_ERROR;
	}
	env_key = string_array_create_key("OLDPWD", 6);
	if (!env_key)
		mini->last_return = MALLOC_ERROR;
	env_row = get_new_env_row(mini, env_key, original_pwd);
	

}