/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:52:25 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/24 09:52:37 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	use_str_left(char *buffer, char *str_left)
{
	ssize_t	buffer_len;

	if (!*str_left)
		return (0);
	buffer_len = 0;
	while (*str_left && *str_left != '\n')
		buffer[buffer_len++] = (*str_left++);
	if (*str_left == '\n')
		buffer[buffer_len++] = (*str_left++);
	buffer[buffer_len] = '\0';
	while (*str_left)
	{
		*(str_left - buffer_len) = *str_left;
		str_left++;
	}
	*(str_left - buffer_len) = '\0';
	return (buffer_len);
}

static void	save_str_left(char *str_left, char *cursor, ssize_t len)
{
	while (len--)
		*(str_left++) = *(cursor++);
	*str_left = '\0';
}

static char	*str_cut(char *buffer, char *cursor, ssize_t line_len)
{
	char	*cut;
	ssize_t	cut_len;

	if (!line_len && cursor == buffer)
		return (0);
	cut_len = cursor - buffer;
	cut = malloc(cut_len + line_len + 1);
	if (!cut)
		return (0);
	cut += cut_len + line_len;
	*cut = '\0';
	while (cut_len--)
		*(--cut) = *(--cursor);
	return (cut);
}

static char	*read_next(int fd, char *str_left, ssize_t line_len)
{
	char	buffer[BUFFER_SIZE];
	char	*cursor;
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (0);
	if (!bytes_read)
		return (str_cut(buffer, buffer, line_len));
	cursor = buffer;
	while (--bytes_read && *cursor != '\n')
		cursor++;
	if (*cursor == '\n')
	{
		save_str_left(str_left, cursor + 1, bytes_read);
		return (str_cut(buffer, cursor + 1, line_len));
	}
	bytes_read = cursor - buffer + 1;
	cursor = read_next(fd, str_left, bytes_read + line_len);
	if (!cursor)
		return (0);
	while (bytes_read--)
		*(--cursor) = buffer[bytes_read];
	return (cursor);
}

char	*get_next_line(int fd)
{
	static char	str_left[BUFFER_SIZE];
	char		buffer[BUFFER_SIZE];
	ssize_t		buffer_len;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buffer_len = use_str_left(buffer, str_left);
	if (buffer_len && buffer[buffer_len - 1] == '\n')
		return (str_cut(buffer, buffer + buffer_len, 0));
	line = read_next(fd, str_left, buffer_len);
	if (!line)
		return (0);
	while (buffer_len--)
		*(--line) = buffer[buffer_len];
	return (line);
}
