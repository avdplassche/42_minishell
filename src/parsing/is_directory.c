#include "minishell.h"

int	is_directory(char *line)
{
	DIR				*folder;
	struct dirent	*s_dir;

	if (!access(line, F_OK))
	{
		folder = opendir(line);
		if (!folder)
			return (0);
		s_dir = readdir(folder);
		if (s_dir->d_type == 4)
			return (closedir(folder), 1);
	}
	closedir(folder);
	return (0);
}
