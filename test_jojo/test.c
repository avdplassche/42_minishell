
#include "../includes/minishell.h"

static	void build_path(char **new_ptr, char *variable, char *path)
{
	char	*key_format_variable;
	(void)new_ptr;
	(void)path;

	key_format_variable = create_key_format(variable, ft_strlen(variable));
	printf("the key format of the variable is %s\n", key_format_variable);
	//return (key_format_variable);
}

/*
	1. get the current working directory
	2. malloc for the new path variable
	3. fill the array wiht the variable and the new path, this is the ifnalised pointer 
*/
static void get_cwd(t_mini *mini, t_cmd *cmd, char *variable)
{
	char		cwd[PATH_MAX];
	char		*ptr_cwd;
	char		*new_ptr;
	(void)cmd;

	ptr_cwd = getcwd(cwd, sizeof(cwd));
	if (!ptr_cwd)
	{
		perror("get_cwd() failed\n");
		mini->last_return = MALLOC_ERROR;
	}
	new_ptr = (char *)malloc(sizeof(char) * (ft_strlen(variable + 1) + ft_strlen(ptr_cwd) + 1));
	if (!new_ptr)
	{
		mini->last_return = MALLOC_ERROR;
		return ;
	}
	build_path(&new_ptr, variable, ptr_cwd);
}	

/*
	1. get the old pointer 
	2. once we have built the new ptr like the path variable, we replace it
	3. if we do not find the old path pointer i need to do a string array push
*/
void replace_in_double_array(t_mini *mini, t_cmd *cmd, char *variable)
{
	//char	*old_path_pointer;
	//char	*new_path_pointer;

	//old_path_pointer = string_array_find_key(mini->envp, variable); //i get the pointer of the PWD variable by finding where it is in the array
	get_cwd(mini, cmd, variable);
}

int main(int argc, char **argv, char **env)
{
	t_mini	mini;
	t_cmd	cmd;
	//char	**test;
	(void)argc;
	(void)argv;

	mini.envp = env;
	replace_in_double_array(&mini, &cmd, "PATH");
	return (0);
}
