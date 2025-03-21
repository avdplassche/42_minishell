
#include "../includes/minishell.h"

static void get_new_pwd(t_mini *mini, char *variable)
{
	char	*new_cwd_ptr;
	char	buffer[PATH_MAX + 1];
	char	*key_formated_variable;

	key_formated_variable = string_array_create_key(variable, ft_strlen(variable));
	printf("key formated variable is %s\n", key_formated_variable);
	new_cwd_ptr = getcwd(buffer, PATH_MAX + 1);
	printf("new cwd is %s\n", new_cwd_ptr);
	if (!new_cwd_ptr)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
}


void	string_array_replace(t_mini *mini, t_cmd *cmd, char *variable)
{
	char	*old_pwd;
	//char	*new_pwd;
	(void)cmd;

	old_pwd = string_array_find_key(mini->envp, variable);
	printf("old pwd is worth %s\n", old_pwd);
	//replace_old_pwd(mini, old_pwd);
	get_new_pwd(mini, variable);
}

	//i have the env pointer given to me 
	// i need to find the pwd pointer in the double array 
	//this needs to be conserved in the OLD PATH variable 
	// i need to create the new pointer by getting the variable with the equal sign and then adding the cwd result behind.
	//once i have this pointer, i need to add the old pwd value as OLDPWD and replace the new one with PWD

int main(int argc, char **argv, char **env)
{
	t_mini	mini;
	t_cmd	cmd;

	(void)argc;
	(void)argv;

	mini.envp = env;
	string_array_replace(&mini, &cmd, "PWD");
	return (0);
}
