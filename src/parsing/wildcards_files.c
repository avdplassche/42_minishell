/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:01 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:40:02 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_dir_start(char *temp, int i)
{
	while (i > 0 && temp[i] != ' ')
		i--;
	if (i == 0)
		return (0);
	else
		return (i + 1);
}

void	set_wildcard_directory(t_mini *mini, t_wildcard *w, int i)
{
	char	buffer[PATH_MAX];

	while (i > 0)
	{
		if (w->wildcard[i] == '/')
			break ;
		i--;
	}
	if (i == 0)
	{
		if (w->wildcard[i] == '/')
			w->dirname = ft_strdup("/");
		else
		{
			getcwd(buffer, PATH_MAX);
			w->dirname = ft_strdup(buffer);
			w->current = true;
		}
	}
	else if (i > -1)
		w->dirname = ft_substr(w->wildcard, 0, i);
	else
		w->dirname = NULL;
	if (i > -1)
		str_malloc_wildcard_check(mini, w, w->dirname);
}

/** Count valid files in order to malloc a char table
 */
int	count_valid_files(t_wildcard *w)
{
	int				count;
	struct dirent	*s_dir;
	DIR				*folder;

	count = 0;
	folder = opendir(w->dirname);
	if (!folder)
		return (0);
	s_dir = readdir(folder);
	while (s_dir)
	{
		if (is_valid_filename(w->token, s_dir, 0, 0))
			count++;
		s_dir = readdir(folder);
	}
	closedir(folder);
	return (count);
}

void	fill_file_list(t_mini *mini, t_wildcard *w)
{
	DIR				*folder;
	struct dirent	*s_dir;
	int				i;

	w->file_list = (char **)malloc(sizeof(char *) * (w->file_amount + 1));
	wildcard_file_list_malloc_check(mini, w);
	i = -1;
	folder = opendir(w->dirname);
	s_dir = readdir(folder);
	while (s_dir)
	{
		if (is_valid_filename(w->token, s_dir, 0, 0))
		{
			w->temp = ft_strdup(s_dir->d_name);
			str_malloc_wildcard_check(mini, w, w->temp);
			w->file_list[++i] = enquote_str(w->temp, '"');
			if (!w->file_list[i])
				return (free_wildcard_double_pointer_first_part(mini, w));
			free_string_ptr(&w->temp);
		}
		s_dir = readdir(folder);
	}
	w->file_list[++i] = NULL;
	closedir(folder);
}

int	is_valid_filename(char *token, struct dirent *s_dir, int i, int j)
{
	int	tok_end;
	int	file_end;

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
		if (!is_valid_filename(token, s_dir, i, j))
			return (0);
	tok_end = ft_strlen(token) - 1;
	file_end = ft_strlen(s_dir->d_name) - 1;
	if (token[tok_end] == '/')
		if (s_dir->d_type == 4)
			return (1);
	while (token[tok_end] != '*')
		if (token[tok_end--] != s_dir->d_name[file_end--])
			return (0);
	return (1);
}
