
#include "../../includes/minishell.h"

//to move in errors




// int	is_valid_redirections(t_mini *mini)
// {
// 	t_quote	q;
// 	int		i;
// 	int		c;

// 	i = 0;
// 	q.sgl = 0;
// 	q.dbl = 0;
// 	while (mini->line[i])
// 	{
// 		quote_enclosure_handle(mini->line[i], &q);
// 		c = 0;
// 		while (mini->line[i] && !q.sgl && !q.dbl && mini->line[i] == '<')
// 		{
// 			i++;
// 			if (++c >= 3)
// 				return (UNEXPECTED_IN_REDIR);
// 		}
// 		c = 0;
// 		while (mini->line[i] && !q.sgl && !q.dbl && mini->line[i] == '>')
// 		{
// 			i++;
// 			if (++c >= 3)
// 				return (UNEXPECTED_OUT_REDIR);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

