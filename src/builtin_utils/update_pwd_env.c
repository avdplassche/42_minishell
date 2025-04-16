
#include "minishell.h"

static void	handle_error(t_mini *mini, char *ptr)
{
	free(ptr);
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
	free_string_ptr(&env_key);
	free_string_ptr(&env_row);
	free_string_ptr(&new_cwd);
	mini->last_return = 0;
	return (mini->last_return);
}

