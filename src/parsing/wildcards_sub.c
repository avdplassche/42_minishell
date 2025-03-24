
#include "minishell.h"


int	count_valid_files(DIR *folder, char *dirname, char *token)
{
	int				count;
	struct dirent	*s_dir;

	count = 0;
	folder = opendir(dirname);
	s_dir = readdir(folder);
	while (s_dir)
	{
		if (is_valid_filename(token, s_dir, 0, 0, 0))
			count++;
		s_dir = readdir(folder);
	}
	closedir(folder);
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

char	*tokenize_wildcard(char *temp, int start)
{
	int		len;
	
	DEBUG("(f)Tokenize_wildcard\n-> temp = %s, start = %d\n\n", temp, start);
	len = start;
	while (start >= 0 && temp[start] != '/')
		start--;
	start ++;
	while (temp[len] && temp[len] != '/')
		len++;
	if (temp[len] == '/')
		len ++;
	return (ft_substr(temp, start, len - start));
}

char	**fill_valid_filename(DIR *folder, char *dirname, char *token, int file_amount)
{
	int				i;
	struct dirent	*s_dir;
	char			**filename;

	if (!file_amount)
		return (NULL);
	DEBUG("\nFile Amount : %d\n", file_amount);
	filename = (char **)malloc(sizeof(char *) * (file_amount + 1));
	if (!filename)
		return (NULL);
	i = -1;
	folder = opendir(dirname);
	s_dir = readdir(folder);
	while (s_dir)
	{
		if (is_valid_filename(token, s_dir, 0, 0, 0))
			filename[++i] = ft_strdup(s_dir->d_name);
		s_dir = readdir(folder);
	}
	filename[++i] = NULL;
	closedir(folder);
	return (filename);
}

void	sort_array(char **filename, int len)
{
	int		i;
	int		j;
	char	*temp;

	while (len > 0)
	{
		i = 0;
		j = 1;
		while (j < len)
		{
			if (ft_strcmp_alpha(filename[i], filename[j]) > 0)
			{
				temp = filename[i];
				filename[i] = filename[j];
				filename[j] = temp;
			}
			i++;
			j++;
		}
		len --;
	}
}

char	*crop_token(char *token)
{
	int		i;
	char	*subtoken;

	i = 0;
	while (token[i] && token[i] != '/')
		i++;
	if (!token[i])
		return (NULL);
	else
		subtoken = ft_substr(token, 0, i);
	return (subtoken);
}



void	add_prefixes_and_suffixes(char **filename, char *dirname, char *token)
{
	char	*subtoken;
	int		len;
	int		i;
	char	*temp;
	char	*dirpath;

	i = -1;
	len = double_array_len(filename);
	subtoken = crop_token(token);
	if (dirname)
	{
		dirpath = ft_strjoin(dirname, "/");
		free(dirname);
	}
	while (++i < len)
	{
		temp = ft_strjoin(dirpath, filename[i]);
		free(filename[i]);
		if (subtoken)
			filename[i] = ft_strjoin(temp, subtoken);
		else
			filename[i] = ft_strdup(temp);
	}
}

char	*substitute_wildcard(char *temp, int i)
{
	DIR				*folder;
	char			*dirname;
	char 			*token;
	struct dirent	*s_dir;
	char			**filename;
	int				file_amount;  //here because of the case where echo * return nothing

	folder = NULL;
	dirname = get_wildcard_directory(temp, i);
	DEBUG("Dirname : %s\n\n", dirname);
	token = tokenize_wildcard(temp, i);
	DEBUG("Token : %s\n", token);
	file_amount = count_valid_files(folder, dirname, token);
	filename = fill_valid_filename(folder, dirname, token, file_amount);
	int k = -1;
	DEBUG("\n");
	while (filename && filename[++k])
		DEBUG("Filename[%d] : %s\n", k, filename[k]);
	sort_array(filename, double_array_len(filename));
	DEBUG("\n");
	k = -1;
	while (filename && filename[++k])
		DEBUG("Filename[%d] : %s\n", k, filename[k]);
	add_prefixes_and_suffixes(filename, dirname, token);
	DEBUG("\n");
	k = -1;
	while (filename && filename[++k])
		DEBUG("Filename[%d] : %s\n", k, filename[k]);

	/* to delete ?*/

	folder = opendir(dirname);
	while (1)
	{
		s_dir = readdir(folder);
		if (!s_dir)
			break ;
		// if (s_dir->d_name[0] != '.')
		// 	DEBUG("%s\n", s_dir->d_name);
	}

	/* /to delete ?*/

	DEBUG("\n");
	closedir(folder);
	free(token);
	free(dirname);
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

	DEBUG("(f)Wildcard_handle\n-> Temp = %s\n\n", temp);
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
