
#include "minishell.h"

/** This function calculate the necessary lenght of the
 * new string after deleting the quotes
 * @param str the string to delete the quote from
 * @return a total amount of char, to be used for malloc
*/
int	strlen_quote_cleaned_command(char *str)
{
	int		i;
	int		j;
	t_quote	q;

	q.dbl = 0;
	q.sgl = 0;
	i = -1;
	j = 0;
	while (str[++i])
	{
		quote_enclosure_handle(str[i], &q);
		if (!is_quote(str[i])
			|| (str[i] == 34 && q.sgl)
			|| (str[i] == 39 && q.dbl))
			j++;
	}
	return (j);
}

/** What is the type of the last quote before i ?
 * @return 's' for single
 * @return 'd' for double
 */
char	last_quote(char *str, int i)
{
	while (--i >= 0)
	{
		if (str[i] == 39)
			return ('s');
		if (str[i] == 34)
			return ('d');
	}
	return (0);
}

/** Fill command structure (for 1 command of the command line)
 * @param cmd the cmd structure containing cmd->commandto fill
 * @param str the string used to epure from (will be freed after the function)
 * @return not set yet, errors
*/
char	*clean_command_quotes(char *str)
{
	int		i;
	int		j;
	t_quote	q;
	char	*dest;

	j = strlen_quote_cleaned_command(str);
	dest = malloc(sizeof(char) * (j + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	q.dbl = 0;
	q.sgl = 0;
	while (str[++i])
	{
		quote_enclosure_handle(str[i], &q);
		if (!is_quote(str[i]) || (str[i] == 34 && q.sgl)
			|| (str[i] == 39 && q.dbl))
			dest[j++] = str[i];
	}
	dest[j] = '\0';
	return (dest);
}

/** Change quote enclosure, taking a char (34 or 39) as argument
 *
*/
void	quote_enclosure_handle(char c, t_quote *q)
{
	if (c == 34 && !q->dbl && !q->sgl)
		q->dbl = 1;
	else if (c == 34 && q->dbl)
		q->dbl = 0;
	else if (c == 39 && !q->sgl && !q->dbl)
		q->sgl = 1;
	else if (c == 39 && q->sgl)
		q->sgl = 0;
}

/** Tests the validity of quotes with an open/closed boolean system
 * @param mini t_mini containing the command line
 * @return 1 for valid quotes, 0 for non valid
 * @note ascii 34 =  "
 * @note ascii 39 =  '
 */
int	is_valid_quote(t_mini *mini)
{
	int		i;
	t_quote	q;

	q.sgl = 0;
	q.dbl = 0;
	i = -1;
	while (mini->line[++i])
		quote_enclosure_handle(mini->line[i], &q);
	if (q.sgl == 1 || q.dbl == 1)
		return (0);
	return (1);
}
