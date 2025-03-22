
#include "../includes/minishell.h"

static	void build_path(char **new_ptr, char *variable, char *path)
{
	char	*key_format_variable;
	char	**temp;
	char	*curr;
	char	*curr2;

	key_format_variable = string_array_create_key(variable, ft_strlen(variable));
	printf("the key format of the variable is %s\n", key_format_variable);
	temp = new_ptr;
	curr = *temp ;
	curr2 = key_format_variable;
	while (*curr2)
	{
		*curr = *curr2;
		curr++;
		curr2++;
	}
	while (*path)
	{
		*curr = *path;
		curr++;
		path++;
	}
	*curr = '\0';
	free(key_format_variable);
	key_format_variable = NULL;
}

/*
	1. get the current working directory
	2. malloc for the new path variable
	3. fill the array wiht the variable and the new path, this is the ifnalised pointer 
*/
static char	*get_cwd(t_mini *mini, t_cmd *cmd, char *variable)
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
	new_ptr = (char *)malloc(sizeof(char) * (ft_strlen(variable) + 1 + ft_strlen(ptr_cwd) + 1));
	if (!new_ptr)
	{
		mini->last_return = MALLOC_ERROR;
		return (NULL);
	}
	build_path(&new_ptr, variable, ptr_cwd);
	free(ptr_cwd);
	printf("new_ptr is now worth %s\n", new_ptr);
	return (new_ptr);
}	

/*
	1. get the old pointer 
	2. once we have built the new ptr like the path variable, we replace it
	3. if we do not find the old path pointer i need to do a string array push
*/
void replace_in_double_array(t_mini *mini, t_cmd *cmd, char *variable)
{
	char	*key_format_pointer;
	char	*new_path_pointer;
	int		i;

	key_format_pointer = string_array_find_string(mini->envp, variable); //i get the pointer of the PWD variable by finding where it is in the array
	new_path_pointer = get_cwd(mini, cmd, variable);
	i = 0;
	while (mini->envp[i])
	{
		if (start_with(mini->envp[i], key_format_pointer))
		{
			free(mini->envp[i]);
			mini->envp[i] = new_path_pointer;
			free(key_format_pointer);
			return ;
		}
		i++;
	}
	free(key_format_pointer);
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



//POINTERS AND IF THEY NEED TO BE FREED 
/*
	p1 : keyformatvarIABLE   ---> PWD= ...old path
	P2 NEWPATH PTR			 ---> PWD new path after the getcwd formula
	mini.envp PTR			---> the doubkle array with the environment variables

	then envp[i] has the same address as the newptr so it points to PATH=neqjnfqjknfjknfekj/dqbuibfq/dnqkbjhq
	key_format pointer needs to be freed after because its been used in the start with function 


*/
