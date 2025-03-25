
#include "minishell.h"


int	count_valid_files(DIR *folder, t_wildcard w)
{
	int				count;
	struct dirent	*s_dir;

	count = 0;
	folder = opendir(w.dirname);
	s_dir = readdir(folder);
	while (s_dir)
	{
		if (is_valid_filename(w.token, s_dir, 0, 0))
			count++;
		s_dir = readdir(folder);
	}
	closedir(folder);
	return (count);
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

char	**fill_file_list(DIR *folder, t_wildcard w, int file_amount)
{
	int				i;
	struct dirent	*s_dir;
	char			**file_list;

	if (!file_amount)
		return (NULL);
	DEBUG("\nFile Amount : %d\n", file_amount);
	file_list = (char **)malloc(sizeof(char *) * (file_amount + 1));
	if (!file_list)
		return (NULL);
	i = -1;
	folder = opendir(w.dirname);
	s_dir = readdir(folder);
	while (s_dir)
	{
		if (is_valid_filename(w.token, s_dir, 0, 0))
			file_list[++i] = ft_strdup(s_dir->d_name);
		s_dir = readdir(folder);
	}
	file_list[++i] = NULL;
	closedir(folder);
	return (file_list);
}

void	sort_array(char **filename, int len)
{
	int		i;
	int		j;
	char	*temp;

	if (len <= 1)
		return ;
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

void	get_prefix(t_wildcard *w, char *temp, int i)
{
	while (i >= 0 && temp[i] != '/')
		i--;
	if (w->current)
		return ;
	else if (i == 0)
		w->prefix = ft_strdup(w->dirname);
	else
		w->prefix = ft_strjoin(w->dirname, "/");
}

void	get_suffix(t_wildcard *w, char *temp, int i)
{
	int	len;

	len = ft_strlen(temp) - 1;
	while (i <= len && temp[i] != '/')
		i++;
	if (temp[i] == '/' && i < len)
		w->suffix = ft_substr(temp, i, len - i + 1);
}



void	change_affixes(char **filename, char *temp, t_wildcard w, int i)
{
	// char	*subtoken;
	int		len;
	int			j;
	// char	*temp;
	// char	*prefix;
	// char	*dirpath;
	(void)i;

	DEBUG("\n(f)Change affixes\n-> dirname = %s, token = %s\n", w.dirname, w.token);
	j = -1;
	len = double_array_len(filename);
	// subtoken = crop_token(w.token);
	// DEBUG("Subtoken : %s\n", subtoken);
	get_prefix(&w, temp, i);
	get_suffix(&w, temp, i);
	// DEBUG("Preffix : %s\n", w.prefix);
	// DEBUG("Suffix : %s\n", w.suffix);
	while (++j < len)
	{
		DEBUG("Filename[%d] : %s%s%s\n", j, w.prefix, filename[j], w.suffix);
	}
	// if (w.dirname[0] == '/')
	// 	dirpath = ft_strdup(w.dirname);
	// else if (w.dirname)
	// {
	// 	dirpath = ft_strjoin(w.dirname, "/");
	// 	free(w.dirname);
	// }
	// while (++j < len)
	// {
	// 	if (dirpath)
	// 		temp = ft_strjoin(dirpath, filename[j]);
	// 	free(filename[j]);
	// 	if (subtoken)
	// 		filename[j] = ft_strjoin(temp, subtoken);
	// 	else
	// 		filename[j] = ft_strdup(temp);
	// }
}

void	set_wildcard_directory(t_wildcard *w, char *temp, int i)
{
	// char	*dirname;
	char	buffer[PATH_MAX];

	while (i > 0)
	{
		if (temp[i] == '/')
			break ;
		i--;
	}
	if (i == 0)
	{
		if (temp[i] == '/')
			w->dirname = ft_strdup("/");
		else
		{
			getcwd(buffer, PATH_MAX);
			w->dirname = ft_strdup(buffer);
			w->current = true;
		}
	}
	else if (i > -1)
		w->dirname = ft_substr(temp, 0, i );
	else
		w->dirname = NULL;
}

void	init_wildcard_struct(t_wildcard *w)
{
	w->dirname = NULL;
	w->token = NULL;
	w->s_dir = NULL;
	w->prefix = NULL;
	w->suffix = NULL;
	w->current = false;
}

char	*substitute_wildcard(char *temp, int i)
{
	t_wildcard		w;
	DIR				*folder;
	char			**file_list;
	int				file_amount;  //here because of the case where echo * return nothing

	folder = NULL;
	init_wildcard_struct(&w);
	set_wildcard_directory(&w, temp, i);
	DEBUG("Dirname : %s\n\n", w.dirname);
	w.token = tokenize_wildcard(temp, i);
	DEBUG("Token : %s\n", w.token);
	DEBUG("Index : %d\n", i);
	file_amount = count_valid_files(folder, w);
	file_list = fill_file_list(folder, w, file_amount);
	print_char_table(file_list, "file_list");
	sort_array(file_list, double_array_len(file_list));
	print_char_table(file_list, "file_list");
	change_affixes(file_list, temp, w, i);
	// print_char_table(file_list, "file_list");

	/* to delete*/

	folder = opendir(w.dirname);
	while (1)
	{
		w.s_dir = readdir(folder);
		if (!w.s_dir)
			break ;
		// if (s_dir->d_name[0] != '.')
		// 	DEBUG("%s\n", s_dir->d_name);
	}

	/* /to delete ?*/

	DEBUG("\n");
	closedir(folder);
	free(w.token);
	free(w.dirname);
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
