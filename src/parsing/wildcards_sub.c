
#include "minishell.h"

/** Count valid files in order to malloc a char table 
 */
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
	char	*token;
	
	DEBUG("(f)Tokenize_wildcard\n-> temp = %s, start = %d\n\n", temp, start);
	len = start;
	while (start >= 0 && temp[start] != '/')
		start--;
	start ++;
	while (temp[len] && temp[len] != '/')
		len++;
	if (temp[len] == '/')
		len ++;
	token = ft_substr(temp, start, len - start);
	//malloc protection
	return (token);
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
	if (temp[len] == '/')
		w->suffix = ft_strdup("/");
	else if (temp[i] == '/' && i < len)
		w->suffix = ft_substr(temp, i, len - i + 1);
}

char	*join_three_strings(char *s1, char *s2, char *s3)
{
	char	*temp1;
	char	*temp2;

	temp1 = NULL;
	temp2 = NULL;
	if (!s1 && !s2 && !s3)
		return (NULL);
	if (!s1 && !s2)
		return (ft_strdup(s3));
	else if (!s1 && !s3)
		return (ft_strdup(s2));
	else if (!s2 && !s3)
		return (ft_strdup(s1));
	else if (!s1)
		return (ft_strjoin(s2, s3));
	else if (!s2)
		return (ft_strjoin(s1, s3));
	else if (!s3)
		return (ft_strjoin(s1, s2));
	else
	{
		temp1 = ft_strjoin(s1, s2);
		temp2 = ft_strjoin(temp1, s3);
		return (free(temp1), temp2);
	}
}


void	change_affixes(char **file_list, char *temp1, t_wildcard *w, int i)
{
	int		len;
	int		j;
	char	*temp2;

	j = -1;
	len = double_array_len(file_list);
	get_prefix(w, temp1, i);
	get_suffix(w, temp1, i);
	DEBUG("\nPrefix = %s\nSuffix : %s\n\n", w->prefix, w->suffix);
	while (++j < len)
	{
		temp2 = ft_strdup(file_list[j]);
		free(file_list[j]);
		file_list[j] = join_three_strings(w->prefix, temp2, w->suffix);
		free(temp2);
	}
}

void	set_wildcard_directory(t_wildcard *w, char *temp, int i)
{
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

void	free_wildcard_struct(t_wildcard *w)
{
	if (w->dirname)
		free(w->dirname);
	if (w->token)
		free(w->token);
	if (w->s_dir)
		free(w->s_dir);
	if (w->prefix)
		free(w->prefix);
	if (w->suffix)
		free(w->suffix);
}

// char	*join_n_string(char **table, int len)
// {
// 	char	*str;
// 	int		i;
// 	int		j;
// 	char	*temp1;
// 	char	*temp2;

// 	i = 0;
// 	j = 1;
// 	if (len = 1)
// 		return (table[0]);
// 	while (j < len)
// 	{
// 		temp1 = ft_strjoin(table[i], " ");
// 		temp2 = ft_strjoin(temp1, table[j]);
// 		free(temp1);
// 		i++;
// 		j++;
// 	}

// }

// void	set_final_substitution(t_wildcard *w, char **file_list)
// {

	
// }

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
	if (!file_amount)
		return (free_wildcard_struct(&w), temp);  //Should I also write on stderr
	DEBUG("Count : %d\n", file_amount);
	file_list = fill_file_list(folder, w, file_amount);
	print_char_table(file_list, "file_list");
	sort_array(file_list, double_array_len(file_list));
	print_char_table(file_list, "file_list");
	change_affixes(file_list, temp, &w, i);
	print_char_table(file_list, "file_list");
	// set_final_substitution(&w, file_list);
	// temp = 

	DEBUG("\n");
	closedir(folder);
	free_wildcard_struct(&w);
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
