
#include "minishell.h"

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

	init_quotes(&q);
	i = -1;
	while (mini->line[++i])
		quote_enclosure_handle(mini->line[i], &q);
	if (q.sgl == 1 || q.dbl == 1)
		return (0);
	return (1);
}
