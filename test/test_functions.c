

// #include "minishell.h"
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
/*This file is used to test if created functions are working as intended */



int main (void)
{
	DIR * folder;
	char buffer[256];
	int i = -1;
	char *dirname = getcwd(buffer, 256);
	struct dirent *s_dir;

	printf("f = %s\n", dirname);
	folder = opendir(dirname);
	while (1)
	{
		s_dir = readdir(folder);
		if (!s_dir)
			break ;
		printf("%s\n", s_dir->d_name);
		printf("%d\n", s_dir->d_type);
		printf("\n");
	}
	// perror("stream : ");
	return (0);
}


// int main(int argc, char **argv, char **envp)
// {
// 	int fd;
// 	char *env;
// 	char needle[] = "vd";
// 	char haystack[] = "Alexvd";


// 	char pathname[] = "/bin/echo";
// 	char *args[] = {pathname, "-nnnn", "Hello World", NULL};

// 	printf("%s\n", getenv("date"));
// 	// if (execve(pathname, args, envp) == -1)
// 	// 	perror("Error");
// 	// printf("string : %s\n", enquote_str(haystack, 34));
// 	// printf("%d\n", contain_string_at_specific_index(haystack, needle, 4));
// 	// printf("%d\n", contain_string_at_specific_index(haystack, needle, 3));
// 	// printf("%s\n", epurstring(str));
// 	// env = getenv("PATH");    //keep those
// 	// printf("%s\n", env);


// 	return (0);
// }
