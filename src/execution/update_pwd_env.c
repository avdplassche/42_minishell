
#include "minishell.h"

void	update_pwd_env(t_mini *mini, char *env_var)
{
	char	*env_row;
	char	*env_key;
	char	*new_cwd;
	
	env_key = string_array_create_key(env_var, ft_strlen(env_var));
	new_cwd = get_current_workdir(mini);
	env_row = get_new_env_row(mini, env_key, new_cwd);
	set_env(mini, env_key, env_row);
	free(env_key);
}
