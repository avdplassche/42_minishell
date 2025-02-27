#include "../includes/minishell.h"

static int	count_len_dest(char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_space(src[i]))
		i++;
	while (src[i])
	{
		while (!(is_space(src[i])))
		{
			i++;
			j++;
		}
		if (is_space(src[i]))
			j++;
		while (is_space(src[i]))
			i++;
	}
	if (is_space(src[i - 1]))
		j--;
	return (j);
}

/** Epur string by deleting all multiple spaces
 * @return an epured string
 */
char *epurstring(char *src)  //may be able to delete the ft_is_only_space lines
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (count_len_dest(src) + 1));
	if (!dest)
		return (NULL);
	while (is_space(src[i]))
		i++;
	while (src[i])
	{
		while (!(is_space(src[i])))
			dest[j++] = src[i++];
		if (is_space(src[i]))
			dest[j++] = ' ';
		while (is_space(src[i]))
			i++;
	}
	if (is_space(src[i - 1]))
		j--;
	dest[j] = '\0';
	free(src);
	return (dest);
}




// char *epur_out_of_quotes(char *src)
// {
// 	int	i;
// 	int	j;
// 	bool	single_quote;
// 	bool	double_quote;

// 	single_quote = 0;
// 	double_quote = 0;
// 	j = 0;
// 	i = 0;
// 	while (is_space(src[1]) && !(is_quote))
// 		i++;




// }
