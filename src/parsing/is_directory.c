#include "minishell.h"

int	is_directory(char *line)
{
	DIR				*folder;
	struct dirent	*s_dir;

	if (access(line, F_OK) == 0)
	{
		folder = opendir(line);
		if (!folder)
			return (0);
	
		s_dir = readdir(folder);
		closedir(folder);
		if (s_dir->d_type == 4)
			return (1);
	}
	return (0);
}
