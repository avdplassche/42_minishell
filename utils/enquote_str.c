

#include "../includes/minishell.h"


/** Single or double enquote a string
 * @param str string to enquote
 * @param q type of quote ( ' or " )
 */
char	*enquote_str(char *str, int q)
{
	int		i;
	int		j;
	char	*enquoted_str;

	j = -1;
	enquoted_str = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!enquoted_str)
		return (NULL);
	enquoted_str[++j] = q;
	i = -1;
	while (str[++i])
		enquoted_str[++j] = str[i];
	i++;
	enquoted_str[i] = q;
	enquoted_str[++i] = '\0';
	// free(str) ?
	return (enquoted_str);
}

