
#include "minishell.h"

static char	*free_stash_and_return(char **stash)
{
	if (!stash)
		return (NULL);
	free(*stash);
	*stash = NULL;
	return (NULL);
}

static char	*update_stash(char	**old_stash)
{
	char	*new_stash;
	char	*line;
	int		i;

	i = 0;
	while ((*old_stash)[i] && (*old_stash)[i] != '\n')
		i++;
	if ((*old_stash)[i] == '\0')
	{
		line = ft_strdup((*old_stash));
		if (!line)
			return (NULL);
		free(*old_stash);
		return (line);
	}
	i++;
	new_stash = ft_substr(*old_stash, i, ft_strlen(*old_stash) - i);
	if (!new_stash)
		return (free_stash_and_return(old_stash));
	free(*old_stash);
	*old_stash = new_stash;
	return (new_stash);
}

static char	*extract_line(char *stash)
{
	int		len;
	char	*line;

	len = 0;
	if (!stash)
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = ft_substr(stash, 0, len);
	return (line);
}

static char	*read_from_stdin(char *stash)
{
	char		buffer[BUFFER_SIZE + 1];
	int			count_bytes;
	char		*temp;

	while (1)
	{
		count_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (count_bytes < 0)
			return (free_stash_and_return(&stash));
		if (count_bytes == 0)
			return (stash);
		buffer[count_bytes] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
			return (free_stash_and_return(&stash));
		free(stash);
		stash = temp;
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

char	*get_line_from_stdin(void)
{
	static char	*stash = NULL;
	char		*line;

	if (read(STDIN_FILENO, 0, 0) < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	stash = read_from_stdin(stash);
	if (!stash || !*stash)
		return (free_stash_and_return(&stash));
	line = extract_line(stash);
	if (line[0] == '\0' || !line)
		return (NULL);
	stash = update_stash(&stash);
	return (line);
}
