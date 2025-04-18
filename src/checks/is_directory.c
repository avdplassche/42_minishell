/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:46 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/18 16:05:27 by jrandet          ###   ########.fr       */
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
