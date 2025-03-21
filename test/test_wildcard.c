// #include <dirent.h>
// #include <unistd.h>
// #include <stdio.h>
#include "../includes/minishell.h"


int	start_by_path(char *temp, int i)
{
	// int	start;

	// start = -1;
	while (--i >= 0)
	{
		if (temp[i] == '/')
			break ;
	}
	return (i);
}


char	*substitude_wildcard(char *temp, int i)
{
	char	*pathname;
	int		start;

	start = start_by_path(temp, i);
	if (start = 0)
		pathname = ft_strdup("/");
	else if (start > -1)
		pathname = ft_substr(temp, 0, start);
	// while (temp[i])
	// if (temp[i] == '/')
	// 	chdir("/");
	// Functions :
	// opendir
	// chdir (pour ../)
	// struct dirent (d_name and d_type),
	// getcwd
	// readdir

	// while (pathname)
	// pathname = get_path(temp, i);
	return (pathname);
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
/**Go through the command and check if a substitution is needed at the beginins,
 *
 */
char	*wildcard_substitution(char *temp)
{
	t_quote	q;
	char	*dest;
	int		i;

	q.sgl = 0;
	q.dbl = 0;
	i = need_wildcard_substitution(temp);
	if (i = -1)
		return (temp);
	while (i != -1)
	{
		temp = substitude_wildcard(temp, i);
		i = need_wildcard_substitution(temp);
		// quote_enclosure_handle(temp[i], temp[i]);
		// if (temp[i] == '*' && !q.sgl && !q.dbl)
		// list all files in the directory
		// Single ENQUOTE all tokens
	}
	return (dest);
}


int main(void)
{
	char temp[] = "../*/*.c";
	char *dest;
	int i;

	dest = wildcard_substitution(temp);
	printf("dest : %s\n\n", substitude_wildcard(temp, i));
	// printf("dest : %s\n\n", dest);
}
