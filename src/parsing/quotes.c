/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:39:42 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/14 14:39:44 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	init_quotes(&q);
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
char	*clean_command_quotes(t_mini *mini, char *str)
{
	int		i;
	int		j;
	t_quote	q;
	char	*dest;

	init_quotes(&q);
	j = strlen_quote_cleaned_command(str);
	dest = malloc(sizeof(char) * (j + 1));
	str_malloc_check(mini, dest);
	i = -1;
	j = 0;
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

void	init_quotes(t_quote *q)
{
	q->sgl = 0;
	q->dbl = 0;
}
