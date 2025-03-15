
#include "../includes/minishell.h"

//cd with only a relative or absolute pat

int	cd(char	*path)
{
	DIR *dirptr;
	
	if (path == NULL || ft_strlen(path) == 0)
	{
		perror("path is invalid\n");
		return (-1);
	}
	if ((dirptr = opendir(path)) != NULL)
	{
		printf("opendir worked\n");
		closedir(dirptr);
	}
	else
	{
		perror("The directory does not exist or is not accessile\n");
		return (-1);
	}
	if (chdir(path) == 0)
	{
		printf("succesfully changed directory.\n");
		pwd();
	}
	return (0);
}
