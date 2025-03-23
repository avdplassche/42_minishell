
#include "minishell.h"

static int	build_old_pwd_path(t_mini *mini, char *original_pwd)
{
	char	*env_key;
	char	*env_row;
	int		status;

	env_key = string_array_create_key("OLDPWD", 6);
	if (!env_key)
	{
		free(original_pwd);
		mini->last_return = MALLOC_ERROR;
		return (1);
	}
	env_row = get_new_env_row(mini, env_key, original_pwd);
	if (!env_row)
	{
		free(env_key);
		free(original_pwd);
		mini->last_return = MALLOC_ERROR;
		return (1);
	}
	status = set_env(mini, env_key, env_row);
	free(env_key);
	return (status);
}

static char	*get_original_pwd(t_mini *mini)
{
	char	*original_pwd;

	original_pwd = ft_get_env(mini, "PWD");
	if (!original_pwd)
	{
		original_pwd = get_current_workdir(mini);
		if (!original_pwd)
		{
			mini->last_return = MALLOC_ERROR;
			return (0);
		}
	}
	return (original_pwd);
}

int	update_old_pwd_env(t_mini *mini)
{
	char	*original_pwd;
	int		status;

	original_pwd = get_original_pwd(mini);
	if (!original_pwd)
	{
		mini->last_return = MALLOC_ERROR;
		return (mini->last_return);
	}
	status = build_old_pwd_path(mini, original_pwd);
	if (status != 0)
		return (mini->last_return);
	mini->last_return = 0;
	return (mini->last_return);
}
