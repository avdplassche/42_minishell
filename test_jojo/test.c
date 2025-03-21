
#include "../includes/minishell.h"

static char	*get_new_path(t_mini *mini, char *variable, char *path)
{
	char	*key_formated_variable;
	char	*new_path;

	key_formated_variable = string_array_create_key(variable, ft_strlen(variable));
	new_path = (char *)malloc(sizeof(char) * (ft_strlen(key_formated_variable) + ft_strlen(path) + 1));
	if (!new_path)
	{
		mini->last_return = MALLOC_ERROR;
		free(new_path);
		return (NULL);
	}
	string_build(&new_path, key_formated_variable, new_path);

	return (new_path);
}

void	update_pwd(t_mini *mini, t_cmd *cmd, char *variable)
{
	char	buffer[PATH_MAX + 1];
	char	*old_pwd_path;
	char	*new_cwd_path;
	int		i;
	(void)cmd;

	new_cwd_path = getcwd(buffer, PATH_MAX + 1);
	printf("new cwd is %s\n", new_cwd_path);
	if (!new_cwd_path)
	{
		mini->last_return = MALLOC_ERROR;
		return (NULL);
	}
	old_pwd_path = string_array_find_key(mini->envp, variable);
	printf("old pwd is worth %s\n", old_pwd_path);
	//replace_old_pwd(mini, old_pwd);
	get_new_pwd(mini, variable, );
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




/*

HEAP : NEW_PWD_PATH using this space in the heap for my program, need to free it afterwards



*/