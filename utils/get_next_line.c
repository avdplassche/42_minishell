/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:31 by alvan-de          #+#    #+#             */
/*   Updated: 2025/03/10 19:10:04 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	tests(int fd, char *buffer, char *leftover)
{
	if (!buffer)
		return (0);
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0 || fd < 0)
		return (free(buffer), free(leftover), 0);
	return (1);
}

static char	*set_line(char *leftover)
{
	int		i;
	
	i = 0;
	while (leftover[i] != '\n' && leftover[i] != '\0')
		i++;
	return (ft_substr(leftover, 0, i + 1));
}

static char	*set_left(char *leftover)
{
	int		i;
	char	*temp;

	i = 0;
	while (leftover[i] != '\n' && leftover[i] != '\0')
		i++;
	temp = ft_substr(leftover, i + 1, ft_strlen(leftover) - (i + 1));
	free(leftover);
	leftover = temp;
	return (leftover);
}

static char	*fill_left(int fd, char *buffer, char *leftover)
{
	char	*temp;
	int		count;

	count = 0;
	while (1)
	{
		if (ft_strchr(leftover, '\n'))
			break ;
		count = read(fd, buffer, BUFFER_SIZE);
		if (count <= -1)
			return (NULL);
		buffer[count] = '\0';
		if (count == 0)
			break ;
		temp = ft_strjoin(leftover, buffer);
		free(leftover);
		leftover = ft_strdup(temp);
		free(temp);
	}
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*buffer;
	char		*line;

	buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!tests(fd, buffer, leftover))
		return (NULL);
	if (!leftover)
		leftover = ft_strdup("");
	leftover = fill_left(fd, buffer, leftover);
	line = set_line(leftover);
	leftover = set_left(leftover);
	free(buffer);
	if (!line)
		return (NULL);
	return (line);
}
