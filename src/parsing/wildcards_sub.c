
#include "minishell.h"


int	count_valid_files(char *dirname, char *token)
{
	DIR				*folder;
	int				count;
	struct dirent	*s_dir;
	// (void) *token;

	count = 0;
	folder = opendir(dirname);
	s_dir = readdir(folder);
	while (s_dir)
	{
		if (is_valid_filename(token, s_dir, 0, 0))
			count++;
		// s_dir = readdir(folder);
	}
	return (count);
}

char	*get_wildcard_directory(char *temp, int i)
{
	char	*dirname;
	char	buffer[256];

	while (i > 0)
	{
		if (temp[i] == '/')
			break ;
		i--;
	}
	if (i == 0)
	{
		if (temp[i] == '/')
			dirname = ft_strdup("/");
		else
		{
			getcwd(buffer, 256);
			dirname = ft_strdup(buffer);
			return(dirname);
		}
	}
	else if (i > -1)
		dirname = ft_substr(temp, 0, i );
	else
		dirname = NULL;
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

char	*tokenize_wildcard(char *temp, int start)
{
	int		end;

	end = start;
	while (--start >= 0 && temp[start] != '/')
		start--;
	start ++;
	while (temp[end] && temp[end] != '/')
		end++;
	return (ft_substr(temp, start, end - start));
}

char	*substitute_wildcard(char *temp, int i)
{
	DIR				*folder;
	char			*dirname;
	char 			*token;
	struct dirent	*s_dir;
	int				file_amount;

	dirname = get_wildcard_directory(temp, i);
	token = tokenize_wildcard(temp, i);
	DEBUG("Dirname : %s\n\n", dirname);
	DEBUG("Token : %s\n\n", token);
	file_amount = count_valid_files(dirname, token);
	DEBUG("File Amount : %d\n\n", file_amount);
	folder = opendir(dirname);
	while (1)
	{
		s_dir = readdir(folder);
		if (!s_dir)
			break ;
		// if (is_valid_sub(s_dir, token))
		if (s_dir->d_name[0] != '.')
			DEBUG("%s\n", s_dir->d_name);
		// DEBUG("Type : %d\n", s_dir->d_type);
	}
	DEBUG("\n");
	closedir(folder);
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
	char	*dest = NULL;
	int		i;
	int		j = 0;

	DEBUG("(f)Wildcard_handle\nTemp = %s\n\n", temp);
	i = need_wildcard_substitution(temp);
	if (i == -1)
		return (temp);
	while (i != -1 && ++j <= 1)
	{
		temp = substitute_wildcard(temp, i);
		i = need_wildcard_substitution(temp);
		// list all files in the directory
		// Single ENQUOTE all tokens
	}
	return (dest);
}
