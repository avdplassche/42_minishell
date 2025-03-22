
#include "minishell.h"

void	replace_pwd_pointer(char ***env, char *old_ptr)
{

}

/*
	in this function, i find the pointer tothe string array 
*/
void	replace_in_double_array(char **env, char *variable)
{
	char	*full_path;
	char	*pwd_string;

	full_path = string_array_find_string(env, variable);
	if (*full_path)
	{
		if (ft_strcmp("PWD", variable) == 0)
		{
			replace_pwd_pointer(&env, full_path);
		}
	}

	printf("%s\n", full_path);
}