
#include "minishell.h"

static int	build_old_pwd_path(t_mini *mini, char *original_pwd_path)
{
	char	*env_key;
	char	*env_row;
	int		status;

	env_key = string_array_create_key("OLDPWD", 6);
	if (!env_key)
	{
		free(original_pwd_path);
		mini->last_return = MALLOC_ERROR;
		return (1);
	}
	env_row = get_new_env_row(mini, env_key, original_pwd_path);
	if (!env_row)
	{
		free(env_key);
		free(original_pwd_path);
		mini->last_return = MALLOC_ERROR;
		return (1);
	}
	status = set_env(mini, "OLDPWD", env_row);
	free(env_key);
	free(env_row);
	free(original_pwd_path);
	return (status);
}

static char	*get_original_pwd_path(t_mini *mini)
{
	char	*original_pwd_path;

	original_pwd_path = ft_get_env(mini, NULL, "PWD");
	if (!original_pwd_path)
	{
		original_pwd_path = get_current_workdir(mini);
		if (!original_pwd_path)
		{
			mini->last_return = MALLOC_ERROR;
			return (0);
		}
	}
	return (original_pwd_path);
}

int	update_old_pwd_env(t_mini *mini)
{
	char	*original_pwd_path;
	int		status;

	original_pwd_path = get_original_pwd_path(mini);
	if (!original_pwd_path)
	{
		mini->last_return = MALLOC_ERROR;
		return (mini->last_return);
	}
	status = build_old_pwd_path(mini, original_pwd_path);
	if (status != 0)
		return (mini->last_return);
	mini->last_return = 0;
	return (mini->last_return);
}
