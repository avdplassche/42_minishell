/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:46 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:41:58 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
