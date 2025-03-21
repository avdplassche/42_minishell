
#include "minishell.h"

#include "../includes/minishell.h"

// int	is_valid_sub(struct dirent *s_dir)
// {




// }

char	*get_wildcard_directory(char *temp, int i)
{
	char	*dirname;
	char	buffer[256];

	while (--i >= 0)
		if (temp[i] == '/')
			break ;
	if (i == 0)
		dirname = ft_strdup("/");
	else if (i > -1)
		dirname = ft_substr(temp, 0, i );
	else
		dirname = getcwd(buffer, 256);
	return (dirname);
}

/*
	Functions :
	opendir
	chdir (pour ../)
	struct dirent (d_name and d_type),
	getcwd
	readdir
*/

char	*substitute_wildcard(char *temp, int i)
{
	DIR		*folder;
	char	*dirname;
	struct dirent *s_dir;

	dirname = get_wildcard_directory(temp, i);
	DEBUG("Dirname : %s\n\n", dirname);
	folder = opendir(dirname);
	s_dir = readdir(folder);
	while (1)
	{
		s_dir = readdir(folder);
		if (!s_dir)
			break ;
		// if (is_valid_sub(s_dir))
		DEBUG("Name : %s\n", s_dir->d_name);
		DEBUG("Type : %d\n", s_dir->d_type);

		DEBUG("\n");
	}
	// open


	return (temp);
}

/**Tests if a substitution is needed
 */
int	need_wildcard_substitution(char *temp)
{
	int		i;
	t_quote	q;

	q.sgl = 0;
	q.dbl = 0;
	i = -1;
	while (temp[++i])
	{
		quote_enclosure_handle(temp[i], &q);
		if (temp[i] == '*' && !q.dbl && !q.sgl)
			return (i);
	}
	return (-1);
}
/**Go through the command and do all the substitutions
 *
 */
char	*wildcard_handle(char *temp)
{
	t_quote	q;
	char	*dest = NULL;
	int		i;
	int		j = 0;

	DEBUG("(f)Wildcard_handle\nTemp = %s\n\n", temp);
	q.sgl = 0;
	q.dbl = 0;
	i = need_wildcard_substitution(temp);
	if (i == -1)
		return (temp);
	while (i != -1 && ++j <= 3)
	{
		temp = substitute_wildcard(temp, i);
		i = need_wildcard_substitution(temp);
		// list all files in the directory
		// Single ENQUOTE all tokens
	}
	return (dest);
}
