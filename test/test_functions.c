

#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
/*This file is used to test if created functions are working as intended */

char	*clean_big_quotes( char *line)
{
	int		len;
	char	*dest;
	int		i;
	int		j;

	len = strlen(line);
	dest = malloc(sizeof(char) * (len - 1));
	i = 0;
	j = -1;
	while (line[++i] && i < len - 1)
		dest[++j] = line[i];
	dest[j] = '\0';
	return (dest);
}


int main (void)
{
	char *s = "\"dhahd\"";
	printf("%s\n", clean_big_quotes(s));
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
