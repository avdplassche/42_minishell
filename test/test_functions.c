

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









// size_t	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char	*enquote_str(char *str, int q)
// {
// 	int		i;
// 	int		j;
// 	char	*enquoted_str;

// 	j = -1;
// 	enquoted_str = malloc(sizeof(char) * (ft_strlen(str) + 3));
// 	enquoted_str[++j] = q;
// 	i = -1;
// 	while (str[++i])
// 		enquoted_str[++j] = str[i];
// 	i++;
// 	enquoted_str[i] = q;
// 	enquoted_str[++i] = '\0';
// 	return (enquoted_str);
// }

// int	dup_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	printf("%d\n", i);
// 	return (i);
// }

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
