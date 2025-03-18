
#include "minishell.h"


int	ft_strcmp_fd(char *path1, char *path2)
{
	int	fd1;
	int	fd2;
	char *buffer1;
	char *buffer2;

	buffer1 = malloc(sizeof(char) * 2);
	buffer2 = malloc(sizeof(char) * 2);
	fd1 = open(path1, O_RDONLY);
	fd2 = open(path2, O_RDONLY);
	while (read(fd1, buffer1, 1) > 0 && read(fd2, buffer2, 1))
		if (buffer1[0] != buffer2[0])
			return (buffer1[0] - buffer2[0]);
	if (read(fd1, buffer1, 1) > 0)
		return (buffer1[0]);
	else if (read(fd2, buffer2, 1))
		return (buffer2[0]);
	close(fd1);
	close(fd2);
	free (buffer1);
	free (buffer2);
	return (0);
}


int	main(int argc, char **argv)
{
	int	comp;

	if (argc != 3)
		return (printf("Wrong argument count.\n"), EXIT_FAILURE);
	comp = ft_strcmp_fd(argv[1], argv[2]);
	if (!comp)
		printf("%s\"%s\" and \"%s\" are identical%s", GREEN, argv[1], argv[2], RESET);
	else
		printf("%s\"%s\" and \"%s\" are different (%d)%s", RED,  argv[1], argv[2], comp, RESET);
	return (0);
}

