

#include "includes/minishell.h"

/**
 * this file is here to test if created functions are working as intended
 *
 */
int	check_line_first_char(char c)
{
	char	*set;
	int		i;

	i = -1;
	set = "|<>?$#%";
	while (set[++i])
		if (c == set[i])
			return (0);
	return (1);
}

int main (void)
{
	char *env;
	int fd;
	env = NULL;

	fd = open("TODO", O_RDONLY);
	printf("%d\n", fd);
	read(fd, env, 10);
	printf("%s\n", env);
	printf("fd 0 : %s\n", ttyname(0));
	printf("fd 1 : %s\n", ttyname(1));
	printf("fd 2 : %s\n", ttyname(2));
	printf("fd 3 : %s\n", ttyname(fd));
}
