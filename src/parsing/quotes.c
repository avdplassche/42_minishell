
#include "../../includes/minishell.h"

/** Tests the validity of quotes with an open/closed boolean system
 * @param mini t_mini containing the command line
 * @return 1 for valid quotes, 0 for non valid
 * @note ascii 34 =  "
 * @note ascii 39 =  '
 */
int	is_valid_quote(t_mini *mini)  // maybe quotes shouldnt be bools but int, and 2 for cat last and open/close ->for norminette
{
	int		i;
	bool	s_quote;
	bool	d_quote;
	char	last;

	s_quote = 0;
	d_quote = 0;
	i = -1;
	while (mini->line[++i])
	{
		if (mini->line[i] == 34 && s_quote == 0)
		{
			s_quote = 1;
			last = 's';
		}
		else if (mini->line[i] == 34 && s_quote == 1)
		{
			s_quote = 0;
			if (d_quote == 1 && last == 'd')
				d_quote = 0;
		}
		else if (mini->line[i] == 39 && d_quote == 0)
		{
			d_quote = 1;
			last = 'd';
		}
		else if (mini->line[i] == 39 && d_quote == 1)
		{
			d_quote = 0;
			if (s_quote == 1 && last == 's')
				s_quote = 0;
		}
	}
	if (s_quote == 1 || d_quote == 1)
		return (0);
	return (1);
}



