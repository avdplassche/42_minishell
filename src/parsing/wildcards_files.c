#include "minishell.h"


int	is_last_asterisk(char *token, int i)
{
	while (token[i++])
		if (token[i] == '*')
			return (0);
	return (1);
}

int	is_valid_filename(char *token, struct dirent *s_dir, int i, int j)
{
	int	tok_end;
	int	file_end;

	if (is_only_specific_char(s_dir->d_name, '.'))
		return (0);
	if (token[0] != '.' && s_dir->d_name[0] == '.')
		return (0);
	while (token[i] && token[i] != '*')
		if (token[i++] != s_dir->d_name[j++])
			return (0);
	while (token[i] == '*')
		i++;
	while (s_dir->d_name[j] && s_dir->d_name[j] != token[i])
		j++;
	if (!is_last_asterisk(token, i))
	{
		if (!is_valid_filename(token, s_dir, i, j))
			return (0);
	}
	else
	{
		tok_end = ft_strlen(token) - 1;
		file_end = ft_strlen(s_dir->d_name) - 1;
		if (token[tok_end] == '/')
			if (s_dir->d_type == 4)
				return (1);
		while (token[tok_end] != '*')
			if (token[tok_end--] != s_dir->d_name[file_end--])
				return (0);
	}
	return (1);
}
