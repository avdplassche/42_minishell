
#include "../../includes/minishell.h"

/** Tells if the amount of quotes is even or odd
 * @param mini t_mini containing the command line
 * @return 1 for even, 0 for odd
 * @note ascii 34 = '
 * @note ascii 39 = "
 */
int	even_quote(t_mini *mini)
{
	int	i;
	int	double_count;
	int	single_count;

	i = -1;
	double_count = 0;
	single_count = 0;
	while (mini->line[++i])
	{
		if (mini->line[i] == 34)
			double_count++;
		if (mini->line[i] == 39)
			single_count++;
	}
	if (double_count % 2 == 1 || double_count % 2 == 1)
		return (0);
	return (1);
}

/** Count number of quotes in command line
 * @param mini t_mini containing the command line
 * @return number of quotes in command line
 * @note 34 = '
 * @note 39 = "
 */
int	is_valid_quote(t_mini *mini)
{
	int	i;
	int	j;

	if (!(contain_char(mini->line, '"')) && !(contain_char(mini->line, 39)))
		return (1);
	j = ft_strlen(mini->line);
	i = 0;
	while (j > i)   /*  To be continued   */
	{
		while (!(is_quote(mini->line[j])))
			j--;
		while (!(is_quote(mini->line[i])))
			i++;
		if (mini->line[i] != mini->line[j])
			return (0);
	}
	return (1);
}