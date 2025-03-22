
#include "minishell.h"

void	update_pwd_env(t_mini *mini, char *env_var)
{
	char	*full_new_path;
	char	*env_key_variable;
	char	*new_cwd;
	
	env_key_variable = string_array_create_key(env_var, ft_strlen(env_var));
	new_cwd = get_current_workdir(mini);
	full_new_path = get_new_path(mini, env_key_variable, new_cwd);
	set_env(mini, env_key_variable, full_new_path);
}
