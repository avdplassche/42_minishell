

#include "includes/minishell.h"

/*This file is used to test if created functions are working as intended */



int	dup_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	printf("%d\n", i);
	return (i);
}

int main(int argc, char **argv, char **envp)
{
	int fd;
	char *env;
	char needle[] = "vd";
	char haystack[] = "Alexvd";

	printf("%d\n", contain_string_at_specific_index(haystack, needle, 4));
	// printf("%d\n", contain_string_at_specific_index(haystack, needle, 3));
	// printf("%s\n", epurstring(str));
	// env = getenv("PATH");    //keep those
	// printf("%s\n", env);
	return (0);
}
