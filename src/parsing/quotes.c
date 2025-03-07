
#include "../../includes/minishell.h"

int	find_first_quote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (is_quote(str[i]))
			return (str[i]);
	return (0);
}


/** This function calculate the necessary lenght of the new string after deleting the quotes
 * @param str the string to delete the quote from
 * @return a total amount of char, to be used for malloc
*/
int	strlen_quote_cleaned_command(char *str)
{
	int		i;
	int		j;
	t_quote	quote;

	quote.dbl = 0;
	quote.sgl = 0;
	i = -1;
	j = 0;
	while (str[++i])
	{
		quote_enclosure_handle(str[i], &quote);
		if (!is_quote(str[i])
			|| (str[i] == 34 && quote.sgl == 1)
			|| (str[i] == 39 && quote.dbl == 1))
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
int	clean_command_quotes(t_cmd *cmd, char *str)
{
	int		i;
	int		j;
	t_quote	quote;

	j = strlen_quote_cleaned_command(str);
	cmd->command = malloc(sizeof(char) * (j + 1));
		//malloc protection
	i = -1;
	j = 0;
	quote.dbl = 0;
	quote.sgl = 0;
	while (str[++i])
	{
		quote_enclosure_handle(str[i], &quote);
		if (!is_quote(str[i])
			|| (str[i] == 34 && quote.sgl == 1)
			|| (str[i] == 39 && quote.dbl == 1))
		{
			cmd->command[j] = str[i];
			j++;
		}
	}
	cmd->command [j] = '\0';
	return (0);
}


/** Change quote enclosure, taking a char (34 or 39) as argument
 *
*/
void	quote_enclosure_handle(char c, t_quote *quote)
{
	if (c == 34 && !quote->dbl && !quote->sgl)
		quote->dbl = 1;
	else if (c == 34 && quote->dbl)
		quote->dbl = 0;
	else if (c == 39 && !quote->sgl && !quote->dbl)
		quote->sgl = 1;
	else if (c == 39 && quote->sgl)
		quote->sgl = 0;
}


/** Tests the validity of quotes with an open/closed boolean system
 * @param mini t_mini containing the command line
 * @return 1 for valid quotes, 0 for non valid
 * @note ascii 34 =  "
 * @note ascii 39 =  '
 */
int	is_valid_quote(t_mini *mini)  // use last_quote
{
	int		i;
	char	last;
	t_quote	quote;

	quote.sgl = 0;
	quote.dbl = 0;
	i = -1;
	while (mini->line[++i])
	{
		if (mini->line[i] == 39 && quote.sgl == 0)
		{
			quote.sgl = 1;
			last = 'd';
		}
		else if (mini->line[i] == 39 && quote.sgl == 1)
		{
			quote.sgl = 0;
			if (quote.dbl == 1 && last == 's')
				quote.dbl = 0;
		}
		else if (mini->line[i] == 34 && quote.dbl == 0)
		{
			quote.dbl = 1;
			last = 's';
		}
		else if (mini->line[i] == 34 && quote.dbl == 1)
		{
			quote.dbl = 0;
			if (quote.sgl == 1 && last == 'd')
				quote.sgl = 0;
		}
	}
	if (quote.sgl == 1 || quote.dbl == 1)
		return (0);
	return (1);
}



